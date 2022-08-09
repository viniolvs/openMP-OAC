#!/bin/bash
make clean
make
DIRETORIO="out"
SIZE=100

for ((j=1 ; j<=8 ; j*=2))
    do
    for ((i=0; i < 10; i++))
        do
        ./sdqm.x $SIZE $j p out >> $DIRETORIO/p$j.csv
        done
    done

for ((i=0; i < 10; i++))
    do
    ./sdqm.x $SIZE 1 s out >> $DIRETORIO/s1.csv
    done