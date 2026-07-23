#!/bin/sh

gcc main.c -std=c99 -O3 -o main && cat input.txt| ./main
