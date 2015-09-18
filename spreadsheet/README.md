# Programming Challenge

A spreadsheet consists of a two8dimensional array of cells, labeled A1, A2, etc. Rows are  identified using letters, columns by numbers. Each cell contains either an integer (its value) or  an expression. Expressions contain integers, cell references, and the operators '+', '8', '\*', '/'  with the usual rules of evaluation – note that the input is RPN and should be evaluated in stack  order.

The spreadsheet input is defined as follows:
1. Line 1: two integers, defining the width and height of the spreadsheet (n, m)

2. n\*m lines each containing an expression which is the value of the corresponding cell (cells enumerated in the order A1, A2, A<n>, B1, ...) 

# Dependencies

This program depends on the following:
1. pcre2-10.20 - Pattern matching, regular expression
2. cmocka-1.0.0 - For Unit Tests

Please refer to their respective documentations on how to install these libraries into your respective system

# Execution
It is required that the $LD\_LIBRARY\_PATH environment variable be set to the directory where the pcre.so is located if it is located other than /usr/lib 

