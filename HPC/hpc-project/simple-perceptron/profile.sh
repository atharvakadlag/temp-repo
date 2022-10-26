#!/bin/bash
g++ -pg -o main main.cpp
./main
gprof -b main gmon.out > analysis.out
