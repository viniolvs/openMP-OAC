#!/bin/bash
gcc media.c -o media.x
DIRETORIO="out"
SIZE=100

echo "Tam Matriz,Sequencial,Paralelo" >> $DIRETORIO/medias.csv
echo -n "$SIZE," >> $DIRETORIO/medias.csv
./media.x $DIRETORIO/s$SIZE.csv >> $DIRETORIO/medias.csv
./media.x $DIRETORIO/p$SIZE.csv >> $DIRETORIO/medias.csv
echo >> $DIRETORIO/medias.csv
