#' @export
parse_css <- function(fil) {

  x <- paste0(readLines(fil), collapse="\n")

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
