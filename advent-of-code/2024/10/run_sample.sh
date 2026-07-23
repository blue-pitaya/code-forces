#!/bin/sh

gcc main.c -std=c99 -O3 -DMAP_W=8 -DMAP_H=8 -o main && cat sample.txt| ./main
