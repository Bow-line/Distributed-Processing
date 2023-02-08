# !/bin/bash

gcc -c -Wall -fPIC -D_GNU_SOURCE biblio.c

gcc biblio.o -shared -o lib_biblio.so

gcc -c program.c -o program.o

gcc program.o -L. -l_biblio -o program.out

