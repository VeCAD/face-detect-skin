#!/bin/bash
reset
rm face_detect
g++ face_detect_gauss.cpp `pkg-config --cflags --libs opencv` -O3 -o face_detect_gauss
./face_detect_gauss
