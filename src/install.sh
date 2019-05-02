make
gcc -I. -o graph main.c -L. -lgraph -g3
./graph 
rm *.o
rm *.a 
