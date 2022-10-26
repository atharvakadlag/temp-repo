g++ -fprofile-arcs -ftest-coverage -o main main.cpp
./main
gcov -b -c main.cpp
