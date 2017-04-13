#!/bin/bash

sox general_alarm.wav -r 11025 -b 8 alarm-16.wav
xxd -i alarm-16.wav alarm.c

sox chirp-data.wav -r 11025 -b 8 chirp-16.wav
xxd -i chirp-16.wav chirp.c
