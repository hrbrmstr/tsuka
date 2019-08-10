#' Parse Cascading Style Sheets
#'
#' Cascading style sheets ("CSS") is a style sheet language used for
#' describing the presentation of a document written in a markup language like
#' HTML, and is designed to enable the separation of presentation and content,
#' including layout, colors, and fonts. Tools are provided to parse CSS content
#' into data frames.
#'
#' @md
#' @name tsuka
#' @keywords internal
#' @importFrom purrr map_df
#' @importFrom tibble tibble as_tibble
#' @importFrom dplyr mutate
#' @importFrom tidyr unnest
#' @author Bob Rudis (bob@@rud.is)
"_PACKAGE"

## usethis namespace: start
#' @useDynLib tsuka, .registration = TRUE
#' @importFrom Rcpp sourceCpp
## usethis namespace: end
NULL