#include "foundation.h"
#include "parser.h"
#include "selector.h"
#include <katana.h>
#include <Rcpp.h>
using namespace Rcpp;

static const char* katana_stringify_value_list(KatanaParser* parser, KatanaArray* values);

static const char* katana_stringify_value(KatanaParser* parser, KatanaValue* value)
{
  // TODO: @(QFish) Handle this more gracefully X).
  char str[256];
  
  switch (value->unit) {
  case KATANA_VALUE_NUMBER:
  case KATANA_VALUE_PERCENTAGE:
  case KATANA_VALUE_EMS:
  case KATANA_VALUE_EXS:
  case KATANA_VALUE_REMS:
  case KATANA_VALUE_CHS:
  case KATANA_VALUE_PX:
  case KATANA_VALUE_CM:
  case KATANA_VALUE_DPPX:
  case KATANA_VALUE_DPI:
  case KATANA_VALUE_DPCM:
  case KATANA_VALUE_MM:
  case KATANA_VALUE_IN:
  case KATANA_VALUE_PT:
  case KATANA_VALUE_PC:
  case KATANA_VALUE_DEG:
  case KATANA_VALUE_RAD:
  case KATANA_VALUE_GRAD:
  case KATANA_VALUE_MS:
  case KATANA_VALUE_S:
  case KATANA_VALUE_HZ:
  case KATANA_VALUE_KHZ:
  case KATANA_VALUE_TURN:
    snprintf(str, sizeof(str), "%s", value->raw);
    break;
  case KATANA_VALUE_IDENT:
    snprintf(str, sizeof(str), "%s", value->string);
    break;
  case KATANA_VALUE_STRING:
    // FIXME: @(QFish) Do we need double quote or not ?
    //            snprintf(str, sizeof(str), "\"%s\"", value->string);
    snprintf(str, sizeof(str), "%s", value->string);
    break;
  case KATANA_VALUE_PARSER_FUNCTION:
  {
    const char* args_str = katana_stringify_value_list(parser, value->function->args);
    snprintf(str, sizeof(str), "%s%s)", value->function->name, args_str);
    katana_parser_deallocate(parser, (void*) args_str);
    break;
  }
  case KATANA_VALUE_PARSER_OPERATOR:
    if (value->iValue != '=') {
      snprintf(str, sizeof(str), " %c ", value->iValue);
    } else {
      snprintf(str, sizeof(str), " %c", value->iValue);
    }
    break;
  case KATANA_VALUE_PARSER_LIST:
    return katana_stringify_value_list(parser, value->list);
    break;
  case KATANA_VALUE_PARSER_HEXCOLOR:
    snprintf(str, sizeof(str), "#%s", value->string);
    break;
  case KATANA_VALUE_URI:
    snprintf(str, sizeof(str), "url(%s)", value->string);
    break;
  default:
    katana_print("KATANA: Unknown Value unit.");
  break;
  }
  
  size_t len = strlen(str);
  char* dest = (char *)katana_parser_allocate(parser, len+1);
  strcpy(dest, str);
  dest[len] = '\0';
  return dest;
}

static const char* katana_stringify_value_list(KatanaParser* parser, KatanaArray* values)
{
  if (NULL == values)
    return NULL;
  KatanaParserString * buffer = (KatanaParserString *)katana_parser_allocate(parser, sizeof(KatanaParserString));
  katana_string_init(parser, buffer);
  for (size_t i = 0; i < values->length; ++i) {
    KatanaValue* value = (KatanaValue *)values->data[i];
    const char* value_str = katana_stringify_value(parser, value);
    katana_string_append_characters(parser, value_str, buffer);
    katana_parser_deallocate(parser, (void*) value_str);
    value_str = NULL;
    if ( i < values->length - 1 ) {
      if ( value->unit != KATANA_VALUE_PARSER_OPERATOR ) {
        if ( i < values->length - 2 ) {
          value = (KatanaValue*)values->data[i+1];
          if ( value->unit != KATANA_VALUE_PARSER_OPERATOR ) {
            katana_string_append_characters(parser, " ", buffer);
          }
        } else {
          katana_string_append_characters(parser, " ", buffer);
        }
      }
    }
  }
  const char * str = katana_string_to_characters(parser, (KatanaParserString*)buffer);
  katana_parser_deallocate(parser, buffer->data);
  katana_parser_deallocate(parser, (void*) buffer);
  return str;
}


// [[Rcpp::export]]
List parse_css(std::string x) {
  
  KatanaOutput *o = katana_parse(
    x.c_str(), x.length(), KatanaParserModeStylesheet
  );
  
  KatanaParser parser;
  parser.options = &kKatanaDefaultOptions;
  
  List orules(o->stylesheet->rules.length);
  
  for (size_t i = 0; i < o->stylesheet->rules.length; ++i) {
    
    KatanaRule* rule = (KatanaRule*)o->stylesheet->rules.data[i];
    
    switch (rule->type) {
    
    case KatanaRuleStyle:
      
      KatanaArray* selectors = ((KatanaStyleRule*)rule)->selectors;
      StringVector selv(selectors->length);
      
      for (size_t j=0; j < selectors->length; ++j) {
        
        KatanaSelector* selector = (KatanaSelector*)(selectors->data[j]);
        KatanaParserString * string = katana_selector_to_string(&parser, selector, NULL);
        const char* text = katana_string_to_characters(&parser, string);
        katana_parser_deallocate(&parser, (void*) string->data);
        katana_parser_deallocate(&parser, (void*) string);

        selv[j] = std::string(text);
        
        katana_parser_deallocate(&parser, (void*) text);
        
      }
      
      KatanaArray* declarations = ((KatanaStyleRule*)rule)->declarations;
      List declv(declarations->length);
      
      for (size_t j = 0; j < declarations->length; ++j) {
        KatanaDeclaration* decl = (KatanaDeclaration*)(declarations->data[j]);
        const char* str = katana_stringify_value_list(&parser, decl->values);
        declv[j] = List::create(
          _["property"] = std::string(decl->property),
          _["value"] = std::string(str)
        );
        katana_parser_deallocate(&parser, (void*) str);
      }
        
      orules[i] = List::create(
        _["selectors"] = selv,
        _["declarations"] = declv
      );
      
      break;
    }
  }

  katana_destroy_output(o);

  return(orules);
  
}
