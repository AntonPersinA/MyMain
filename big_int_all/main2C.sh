clear
gcc big_int/big_int.c lib/lib.c test/test.c main2.c -lmpfr -o main -lm -O3 -march=native
./main
