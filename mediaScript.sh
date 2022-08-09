#!/bin/bash
gcc media.c -o media.x
DIRETORIO="out"
SIZE=100

echo "Tam Matriz,Número de threads,Tempo médio" >> $DIRETORIO/medias.csv
for ((j=1 ; j<=8 ; j*=2))
    do
    echo -n "$SIZE," >> $DIRETORIO/medias.csv
    echo -n "$j," >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/p$j.csv >> $DIRETORIO/medias.csv
    echo >> $DIRETORIO/medias.csv
    done

echo >> $DIRETORIO/medias.csv

echo "Tam Matriz,Tempo médio" >> $DIRETORIO/medias.csv
    echo -n "$SIZE," >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/s1.csv >> $DIRETORIO/medias.csv
echo >> $DIRETORIO/medias.csv
