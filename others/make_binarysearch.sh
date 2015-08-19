#!/bin/sh

clang -ggdb3 -O0 -std=c99 -Wall -Werror -o binarysearch binarysearch.c sort.c
