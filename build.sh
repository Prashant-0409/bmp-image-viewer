#!/bin/bash

gcc src/bmp_viewer.c src/features.c -o src/final -lSDL2 # compile the program
src/final pictures/test_1.bmp # run the program with a test image