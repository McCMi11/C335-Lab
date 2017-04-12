#!/bin/bash

sox chirp-data.wav -r 11025 -b 16 500hz-16.wav
xxd -i 500hz-16.wav 500hz.c
