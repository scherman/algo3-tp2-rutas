#!/bin/bash

echo acaaa

rm -rf test_k
mkdir test_k
mkdir test_k/img

for i in {100..500..10}
do
	echo generando caso de test para k de tamanio $i...
	./genGrafo 500 $((500*(500/4))) $((500*(500/4)/4)) 1 $((500+1)) $i > test_k/caso_${i}.test
done

echo corriendo tests para k:
python correr.py ../../a.out test_k test_k/img 2
echo tests para k corridos
