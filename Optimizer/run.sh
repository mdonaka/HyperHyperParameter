CXX="g++-10 -std=c++2a -Wall -Wextra -O2"
$CXX -o build/main.o main.cpp -c &&
$CXX -o build/DE.o DE.cpp -c &&
$CXX -o build/Function.o Function.cpp -c &&

$CXX -o build/run build/main.o build/DE.o build/Function.o &&
./build/run
