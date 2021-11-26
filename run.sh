#/bin/bash

c++ -I lib/eigen-3.4.0 src/maintest.cpp src/libODE.cpp -o bin/maintest && bin/maintest
bin/maintest