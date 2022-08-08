#!/bin/bash
make
DIRETORIO="out"
SIZE=100
for ((i=0; i < 10; i++))
    do
    ./sdqm.x $SIZE $SIZE s out >> $DIRETORIO/s$SIZE.csv
    ./sdqm.x $SIZE $SIZE p out >> $DIRETORIO/p$SIZE.csv
    done
