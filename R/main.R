.doparse <- function(x) {

  ret <- .Call(`_tsuka_parse_css`, x)

  purrr::map_df(ret, ~{
    tibble::tibble(
      selectors = .x$selectors
    ) %>%
      dplyr::mutate(declarations = list(
        purrr::map_df(.x$declarations, tibble::as_tibble)
      )) %>%
      tidyr::unnest()
  })

}


#' Parse CSS text intoa data frame
#'
#' @param css a character vector of CSS fulrs
#' @export
parse_css_text <- function(css) {

  .doparse(paste0(css, collapse="\n"))

}

#' Parse a CSS file into a data frame
#'
#' @param fil path to CSS file (will be [path.expand()]ed)
#' @export
parse_css_file <- function(fil) {

  .doparse(paste0(readLines(fil), collapse="\n"))

}
