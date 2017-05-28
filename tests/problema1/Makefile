CC=g++
CFLAGS=--std=c++11

gengrafo: genGrafo.cpp
	$(CC) -o genGrafo genGrafo.cpp $(CFLAGS)

tests: gengrafo
	chmod +x correr.py
	chmod +x genTestN.sh
	chmod +x genTestK.sh
	
	./genTestN.sh
	./genTestK.sh

.PHONY: clean

clean:
	rm -rf genGrafo
