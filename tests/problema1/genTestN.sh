#!/bin/bash

rm -rf test_n
mkdir test_n
mkdir test_n/img

for i in {100..500..10}
do
	echo generando caso de test para n de tamanio $i...
	./genGrafo $i $((i*(i/4))) $((i*(i/4)/4)) 1 $((i+1)) 20 > test_n/caso_${i}.test
done

echo corriendo tests para n:
python correr.py ../../a.out test_n test_n/img 2
echo tests para n corridos
