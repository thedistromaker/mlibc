#!/bin/bash

if [ ! gcc -c mlibc.c -o mlibc-static.o ]; then
  echo "ERROR"
  exit 1
fi
echo "  CC  mlibc-static.o"
if [ ! ar rcs libmlibc.a mlibc-static.o ]; then
  echo "ERROR"
  exit 1
fi
echo "  AR  libmlibc.a"
if [ ! gcc -fPIC -fPIE mlibc.c -o mlibc-shared.o ]; then
  echo "ERROR"
  exit 1
fi
echo "  CC  mlibc-shared.o"
if [ ! gcc -shared mlibc-shared.o -o libmlibc.so ]; then
  echo "ERROR"
  exit 1
fi
echo "  LD  libmlibc.so"
exit 0
