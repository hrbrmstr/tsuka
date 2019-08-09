
# tsuka

## Description

## What’s Inside The Tin

You need to install <https://github.com/hackers-painters/katana-parser>
as a system library that is reachable by the R compilation defaults.

In `src/` there are some header files copied from the `katana` src which
enable use of the same utility functions they use.

The following functions are implemented:

  - `parse_css`: parse a CSS file into a data frame

## Usage

``` r
library(tsuka)

# current version
packageVersion("tsuka")
## [1] '0.1.0'
```

``` r
parse_css(system.file("extdat/sample.css", package = "tsuka"))
## # A tibble: 230 x 3
##    selectors property        value   
##    <chr>     <chr>           <chr>   
##  1 .fc       direction       ltr     
##  2 .fc       text-align      left    
##  3 .fc table border-collapse collapse
##  4 .fc table border-spacing  0       
##  5 html .fc  font-size       1em     
##  6 .fc table font-size       1em     
##  7 .fc td    padding         0       
##  8 .fc td    vertical-align  top     
##  9 .fc th    padding         0       
## 10 .fc th    vertical-align  top     
## # … with 220 more rows
```

## tsuka Metrics

| Lang         | \# Files |  (%) | LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | --: | ---: | ----------: | ---: | -------: | ---: |
| C/C++ Header |        6 | 0.43 | 580 | 0.75 |         238 | 0.81 |      245 | 0.80 |
| C++          |        2 | 0.14 | 168 | 0.22 |          32 | 0.11 |        7 | 0.02 |
| R            |        5 | 0.36 |  22 | 0.03 |           9 | 0.03 |       30 | 0.10 |
| Rmd          |        1 | 0.07 |   8 | 0.01 |          16 | 0.05 |       26 | 0.08 |

## Code of Conduct

Please note that this project is released with a [Contributor Code of
Conduct](CONDUCT.md). By participating in this project you agree to
abide by its terms.
