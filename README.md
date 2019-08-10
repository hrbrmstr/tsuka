
[![Project Status: Concept – Minimal or no implementation has been done
yet, or the repository is only intended to be a limited example, demo,
or
proof-of-concept.](https://www.repostatus.org/badges/latest/concept.svg)](https://www.repostatus.org/#concept)
[![Signed
by](https://img.shields.io/badge/Keybase-Verified-brightgreen.svg)](https://keybase.io/hrbrmstr)
![Signed commit
%](https://img.shields.io/badge/Signed_Commits-100%25-lightgrey.svg)
[![Linux build
Status](https://travis-ci.org/hrbrmstr/tsuka.svg?branch=master)](https://travis-ci.org/hrbrmstr/tsuka)  
![Minimal R
Version](https://img.shields.io/badge/R%3E%3D-3.2.0-blue.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

# tsuka

Parse Cascading Style Sheets

## Description

Cascading style sheets (“CSS”) is a style sheet language used for
describing the presentation of a document written in a markup language
like HTML, and is designed to enable the separation of presentation and
content, including layout, colors, and fonts. Tools are provided to
parse CSS content into data frames.

## SOME IMPORTANT DETAILS

Threw this together for [@clauswilke](https://github.com/clauswilke) &
[{ggtext}](https://github.com/clauswilke/ggtext) based on [this Twitter
convo](https://twitter.com/hrbrmstr/status/1159920814801731586). I am
unlikely to work on this more w/o serious prodding. It only handles CSS
style rules and need 7 other enums covered from
[`katana`](https://github.com/hackers-painters/katana-parser/blob/master/src/katana.h#L38-L48),
plus the core cpp code need to be refactored into functions.

You need to install the
[`katana`](https://github.com/hackers-painters/katana-parser) C99 parser
as a system library that is reachable by the R source package
compilation defaults. It looks to be pretty straightforward to embed the
`katana` source into a C\[++\]-backed R package but that wasn’t the
point of this exercise.

In `src/` there are some header files copied from the `katana` src which
enable use of the same utility functions they use.

## What’s Inside The Tin

The following functions are implemented:

  - `parse_css_file`: Parse a CSS file into a data frame
  - `parse_css_text`: Parse CSS text intoa data frame

## Installation

``` r
remotes::install_git("https://git.rud.is/hrbrmstr/tsuka.git")
# or
remotes::install_git("https://git.sr.ht/~hrbrmstr/tsuka")
# or
remotes::install_gitlab("hrbrmstr/tsuka")
# or
remotes::install_bitbucket("hrbrmstr/tsuka")
# or
remotes::install_github("hrbrmstr/tsuka")
```

NOTE: To use the ‘remotes’ install options you will need to have the
[{remotes} package](https://github.com/r-lib/remotes) installed. \#\#
Usage

``` r
library(tsuka)

# current version
packageVersion("tsuka")
## [1] '0.1.0'
```

``` r
"
/* Applies to the entire body of the HTML document (except where overridden by more specific
selectors). */
body {
  margin: 25px;
  background-color: rgb(240,240,240);
  font-family: arial, sans-serif;
  font-size: 14px;
}

/* Applies to all <h1>...</h1> elements. */
h1 {
  font-size: 35px;
  font-weight: normal;
  margin-top: 5px;
}

/* Applies to all elements with <... class='someclass'> specified. */
.someclass { color: red; }

/* Applies to the element with <... id='someid'> specified. */
#someid { color: green; }
" -> css_ex

parse_css_text(css_ex)
```

<div class="kable-table">

| selectors  | property         | value                |
| :--------- | :--------------- | :------------------- |
| body       | margin           | 25px                 |
| body       | background-color | rgb(240 , 240 , 240) |
| body       | font-family      | arial , sans-serif   |
| body       | font-size        | 14px                 |
| h1         | font-size        | 35px                 |
| h1         | font-weight      | normal               |
| h1         | margin-top       | 5px                  |
| .someclass | color            | red                  |
| \#someid   | color            | green                |

</div>

``` r
parse_css_file(system.file("extdat/sample.css", package = "tsuka"))
```

<div class="kable-table">

| selectors                                  | property            | value              |
| :----------------------------------------- | :------------------ | :----------------- |
| .fc                                        | direction           | ltr                |
| .fc                                        | text-align          | left               |
| .fc table                                  | border-collapse     | collapse           |
| .fc table                                  | border-spacing      | 0                  |
| html .fc                                   | font-size           | 1em                |
| .fc table                                  | font-size           | 1em                |
| .fc td                                     | padding             | 0                  |
| .fc td                                     | vertical-align      | top                |
| .fc th                                     | padding             | 0                  |
| .fc th                                     | vertical-align      | top                |
| .fc-header td                              | white-space         | nowrap             |
| .fc-header-left                            | width               | 25%                |
| .fc-header-left                            | text-align          | left               |
| .fc-header-center                          | text-align          | center             |
| .fc-header-right                           | width               | 25%                |
| .fc-header-right                           | text-align          | right              |
| .fc-header-title                           | display             | inline-block       |
| .fc-header-title                           | vertical-align      | top                |
| .fc-header-title h2                        | margin-top          | 0                  |
| .fc-header-title h2                        | white-space         | nowrap             |
| .fc .fc-header-space                       | padding-left        | 10px               |
| .fc-header .fc-button                      | margin-bottom       | 1em                |
| .fc-header .fc-button                      | vertical-align      | top                |
| .fc-header .fc-button                      | margin-right        | \-1px              |
| .fc-header .fc-corner-right                | margin-right        | 1px                |
| .fc-header .ui-corner-right                | margin-right        | 0                  |
| .fc-header .fc-state-hover                 | z-index             | 2                  |
| .fc-header .ui-state-hover                 | z-index             | 2                  |
| .fc-header .fc-state-down                  | z-index             | 3                  |
| .fc-header .fc-state-active                | z-index             | 4                  |
| .fc-header .ui-state-active                | z-index             | 4                  |
| .fc-content                                | clear               | both               |
| .fc-view                                   | width               | 100%               |
| .fc-view                                   | overflow            | hidden             |
| .fc-widget-header                          | border              | 1px solid \#ccc    |
| .fc-widget-content                         | border              | 1px solid \#ccc    |
| .fc-state-highlight                        | background          | \#ffc              |
| .fc-cell-overlay                           | background          | \#9cf              |
| .fc-cell-overlay                           | opacity             | .2                 |
| .fc-cell-overlay                           | filter              | alpha(opacity =20) |
| .fc-button                                 | position            | relative           |
| .fc-button                                 | display             | inline-block       |
| .fc-button                                 | cursor              | pointer            |
| .fc-state-default                          | border-style        | solid              |
| .fc-state-default                          | border-width        | 1px 0              |
| .fc-button-inner                           | position            | relative           |
| .fc-button-inner                           | float               | left               |
| .fc-button-inner                           | overflow            | hidden             |
| .fc-state-default .fc-button-inner         | border-style        | solid              |
| .fc-state-default .fc-button-inner         | border-width        | 0 1px              |
| .fc-button-content                         | position            | relative           |
| .fc-button-content                         | float               | left               |
| .fc-button-content                         | height              | 1.9em              |
| .fc-button-content                         | line-height         | 1.9em              |
| .fc-button-content                         | padding             | 0 .6em             |
| .fc-button-content                         | white-space         | nowrap             |
| .fc-button-content .fc-icon-wrap           | position            | relative           |
| .fc-button-content .fc-icon-wrap           | float               | left               |
| .fc-button-content .fc-icon-wrap           | top                 | 50%                |
| .fc-button-content .ui-icon                | position            | relative           |
| .fc-button-content .ui-icon                | float               | left               |
| .fc-button-content .ui-icon                | margin-top          | \-50%              |
| .fc-state-default .fc-button-effect        | position            | absolute           |
| .fc-state-default .fc-button-effect        | top                 | 50%                |
| .fc-state-default .fc-button-effect        | left                | 0                  |
| .fc-state-default .fc-button-effect span   | position            | absolute           |
| .fc-state-default .fc-button-effect span   | top                 | \-100px            |
| .fc-state-default .fc-button-effect span   | left                | 0                  |
| .fc-state-default .fc-button-effect span   | width               | 500px              |
| .fc-state-default .fc-button-effect span   | height              | 100px              |
| .fc-state-default .fc-button-effect span   | border-width        | 100px 0 0 1px      |
| .fc-state-default .fc-button-effect span   | border-style        | solid              |
| .fc-state-default .fc-button-effect span   | border-color        | \#fff              |
| .fc-state-default .fc-button-effect span   | background          | \#444              |
| .fc-state-default .fc-button-effect span   | opacity             | .09                |
| .fc-state-default .fc-button-effect span   | filter              | alpha(opacity =9)  |
| .fc-state-default                          | border-style        | solid              |
| .fc-state-default                          | border-color        | \#ccc \#bbb \#aaa  |
| .fc-state-default                          | background          | \#F3F3F3           |
| .fc-state-default                          | color               | \#000              |
| .fc-state-default .fc-button-inner         | border-style        | solid              |
| .fc-state-default .fc-button-inner         | border-color        | \#ccc \#bbb \#aaa  |
| .fc-state-default .fc-button-inner         | background          | \#F3F3F3           |
| .fc-state-default .fc-button-inner         | color               | \#000              |
| .fc-state-hover                            | border-color        | \#999              |
| .fc-state-hover .fc-button-inner           | border-color        | \#999              |
| .fc-state-down                             | border-color        | \#555              |
| .fc-state-down                             | background          | \#777              |
| .fc-state-down .fc-button-inner            | border-color        | \#555              |
| .fc-state-down .fc-button-inner            | background          | \#777              |
| .fc-state-active                           | border-color        | \#555              |
| .fc-state-active                           | background          | \#777              |
| .fc-state-active                           | color               | \#fff              |
| .fc-state-active .fc-button-inner          | border-color        | \#555              |
| .fc-state-active .fc-button-inner          | background          | \#777              |
| .fc-state-active .fc-button-inner          | color               | \#fff              |
| .fc-state-disabled                         | color               | \#999              |
| .fc-state-disabled                         | border-color        | \#ddd              |
| .fc-state-disabled .fc-button-inner        | color               | \#999              |
| .fc-state-disabled .fc-button-inner        | border-color        | \#ddd              |
| .fc-state-disabled                         | cursor              | default            |
| .fc-state-disabled .fc-button-effect       | display             | none               |
| .fc-event                                  | border-style        | solid              |
| .fc-event                                  | border-width        | 0                  |
| .fc-event                                  | font-size           | .85em              |
| .fc-event                                  | cursor              | default            |
| a.fc-event                                 | cursor              | pointer            |
| .fc-event-draggable                        | cursor              | pointer            |
| a.fc-event                                 | text-decoration     | none               |
| .fc-rtl .fc-event                          | text-align          | right              |
| .fc-event-skin                             | border-color        | \#36c              |
| .fc-event-skin                             | background-color    | \#36c              |
| .fc-event-skin                             | color               | \#fff              |
| .fc-event-inner                            | position            | relative           |
| .fc-event-inner                            | width               | 100%               |
| .fc-event-inner                            | height              | 100%               |
| .fc-event-inner                            | border-style        | solid              |
| .fc-event-inner                            | border-width        | 0                  |
| .fc-event-inner                            | overflow            | hidden             |
| .fc-event-time                             | padding             | 0 1px              |
| .fc-event-title                            | padding             | 0 1px              |
| .fc .ui-resizable-handle                   | display             | block              |
| .fc .ui-resizable-handle                   | position            | absolute           |
| .fc .ui-resizable-handle                   | z-index             | 99999              |
| .fc .ui-resizable-handle                   | overflow            | hidden             |
| .fc .ui-resizable-handle                   | font-size           | 300%               |
| .fc .ui-resizable-handle                   | line-height         | 50%                |
| .fc-event-hori                             | border-width        | 1px 0              |
| .fc-event-hori                             | margin-bottom       | 1px                |
| .fc-event-hori .ui-resizable-e             | top                 | 0                  |
| .fc-event-hori .ui-resizable-e             | right               | \-3px              |
| .fc-event-hori .ui-resizable-e             | width               | 7px                |
| .fc-event-hori .ui-resizable-e             | height              | 100%               |
| .fc-event-hori .ui-resizable-e             | cursor              | e-resize           |
| .fc-event-hori .ui-resizable-w             | top                 | 0                  |
| .fc-event-hori .ui-resizable-w             | left                | \-3px              |
| .fc-event-hori .ui-resizable-w             | width               | 7px                |
| .fc-event-hori .ui-resizable-w             | height              | 100%               |
| .fc-event-hori .ui-resizable-w             | cursor              | w-resize           |
| .fc-event-hori .ui-resizable-handle        | \_padding-bottom    | 14px               |
| .fc-corner-left                            | margin-left         | 1px                |
| .fc-corner-left .fc-button-inner           | margin-left         | \-1px              |
| .fc-corner-left .fc-event-inner            | margin-left         | \-1px              |
| .fc-corner-right                           | margin-right        | 1px                |
| .fc-corner-right .fc-button-inner          | margin-right        | \-1px              |
| .fc-corner-right .fc-event-inner           | margin-right        | \-1px              |
| .fc-corner-top                             | margin-top          | 1px                |
| .fc-corner-top .fc-event-inner             | margin-top          | \-1px              |
| .fc-corner-bottom                          | margin-bottom       | 1px                |
| .fc-corner-bottom .fc-event-inner          | margin-bottom       | \-1px              |
| .fc-corner-left .fc-event-inner            | border-left-width   | 1px                |
| .fc-corner-right .fc-event-inner           | border-right-width  | 1px                |
| .fc-corner-top .fc-event-inner             | border-top-width    | 1px                |
| .fc-corner-bottom .fc-event-inner          | border-bottom-width | 1px                |
| table.fc-border-separate                   | border-collapse     | separate           |
| .fc-border-separate th                     | border-width        | 1px 0 0 1px        |
| .fc-border-separate td                     | border-width        | 1px 0 0 1px        |
| .fc-border-separate th.fc-last             | border-right-width  | 1px                |
| .fc-border-separate td.fc-last             | border-right-width  | 1px                |
| .fc-border-separate tr.fc-last th          | border-bottom-width | 1px                |
| .fc-border-separate tr.fc-last td          | border-bottom-width | 1px                |
| .fc-border-separate tbody tr.fc-first td   | border-top-width    | 0                  |
| .fc-border-separate tbody tr.fc-first th   | border-top-width    | 0                  |
| .fc-grid th                                | text-align          | center             |
| .fc-grid .fc-day-number                    | float               | right              |
| .fc-grid .fc-day-number                    | padding             | 0 2px              |
| .fc-grid .fc-other-month .fc-day-number    | opacity             | 0.3                |
| .fc-grid .fc-other-month .fc-day-number    | filter              | alpha(opacity =30) |
| .fc-grid .fc-day-content                   | clear               | both               |
| .fc-grid .fc-day-content                   | padding             | 2px 2px 1px        |
| .fc-grid .fc-event-time                    | font-weight         | bold               |
| .fc-rtl .fc-grid .fc-day-number            | float               | left               |
| .fc-rtl .fc-grid .fc-event-time            | float               | right              |
| .fc-agenda table                           | border-collapse     | separate           |
| .fc-agenda-days th                         | text-align          | center             |
| .fc-agenda .fc-agenda-axis                 | width               | 50px               |
| .fc-agenda .fc-agenda-axis                 | padding             | 0 4px              |
| .fc-agenda .fc-agenda-axis                 | vertical-align      | middle             |
| .fc-agenda .fc-agenda-axis                 | text-align          | right              |
| .fc-agenda .fc-agenda-axis                 | white-space         | nowrap             |
| .fc-agenda .fc-agenda-axis                 | font-weight         | normal             |
| .fc-agenda .fc-day-content                 | padding             | 2px 2px 1px        |
| .fc-agenda-days .fc-agenda-axis            | border-right-width  | 1px                |
| .fc-agenda-days .fc-col0                   | border-left-width   | 0                  |
| .fc-agenda-allday th                       | border-width        | 0 1px              |
| .fc-agenda-allday .fc-day-content          | min-height          | 34px               |
| .fc-agenda-allday .fc-day-content          | \_height            | 34px               |
| .fc-agenda-divider-inner                   | height              | 2px                |
| .fc-agenda-divider-inner                   | overflow            | hidden             |
| .fc-widget-header .fc-agenda-divider-inner | background          | \#eee              |
| .fc-agenda-slots th                        | border-width        | 1px 1px 0          |
| .fc-agenda-slots td                        | border-width        | 1px 0 0            |
| .fc-agenda-slots td                        | background          | none               |
| .fc-agenda-slots td div                    | height              | 20px               |
| .fc-agenda-slots tr.fc-slot0 th            | border-top-width    | 0                  |
| .fc-agenda-slots tr.fc-slot0 td            | border-top-width    | 0                  |
| .fc-agenda-slots tr.fc-minor th            | border-top-style    | dotted             |
| .fc-agenda-slots tr.fc-minor td            | border-top-style    | dotted             |
| .fc-event-vert                             | border-width        | 0 1px              |
| .fc-event-vert .fc-event-head              | position            | relative           |
| .fc-event-vert .fc-event-head              | z-index             | 2                  |
| .fc-event-vert .fc-event-head              | width               | 100%               |
| .fc-event-vert .fc-event-head              | overflow            | hidden             |
| .fc-event-vert .fc-event-content           | position            | relative           |
| .fc-event-vert .fc-event-content           | z-index             | 2                  |
| .fc-event-vert .fc-event-content           | width               | 100%               |
| .fc-event-vert .fc-event-content           | overflow            | hidden             |
| .fc-event-vert .fc-event-time              | white-space         | nowrap             |
| .fc-event-vert .fc-event-time              | font-size           | 10px               |
| .fc-event-vert .fc-event-bg                | position            | absolute           |
| .fc-event-vert .fc-event-bg                | z-index             | 1                  |
| .fc-event-vert .fc-event-bg                | top                 | 0                  |
| .fc-event-vert .fc-event-bg                | left                | 0                  |
| .fc-event-vert .fc-event-bg                | width               | 100%               |
| .fc-event-vert .fc-event-bg                | height              | 100%               |
| .fc-event-vert .fc-event-bg                | background          | \#fff              |
| .fc-event-vert .fc-event-bg                | opacity             | .3                 |
| .fc-event-vert .fc-event-bg                | filter              | alpha(opacity =30) |
| .fc .ui-draggable-dragging .fc-event-bg    | display             | none\\9            |
| .fc-select-helper .fc-event-bg             | display             | none\\9            |
| .fc-event-vert .ui-resizable-s             | bottom              | 0                  |
| .fc-event-vert .ui-resizable-s             | width               | 100%               |
| .fc-event-vert .ui-resizable-s             | height              | 8px                |
| .fc-event-vert .ui-resizable-s             | overflow            | hidden             |
| .fc-event-vert .ui-resizable-s             | line-height         | 8px                |
| .fc-event-vert .ui-resizable-s             | font-size           | 11px               |
| .fc-event-vert .ui-resizable-s             | font-family         | monospace          |
| .fc-event-vert .ui-resizable-s             | text-align          | center             |
| .fc-event-vert .ui-resizable-s             | cursor              | s-resize           |
| .fc-agenda .ui-resizable-resizing          | \_overflow          | hidden             |

</div>

## tsuka Metrics

| Lang         | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C/C++ Header |        6 | 0.43 | 580 | 0.72 |         238 | 0.77 |      245 | 0.74 |
| C++          |        2 | 0.14 | 168 | 0.21 |          32 | 0.10 |        7 | 0.02 |
| Rmd          |        1 | 0.07 |  29 | 0.04 |          24 | 0.08 |       37 | 0.11 |
| R            |        5 | 0.36 |  27 | 0.03 |          15 | 0.05 |       40 | 0.12 |

## Code of Conduct

Please note that this project is released with a [Contributor Code of
Conduct](CONDUCT.md). By participating in this project you agree to
abide by its terms.
