problema1:
	g++ -o problema1 problema1.cpp --std=c++11
	chmod +x problema1
	
problema2:
	g++ -o problema2 problema2.cpp --std=c++11
	chmod +x problema2

problema3:
	g++ -o problema3 problema3.cpp --std=c++11
	chmod +x problema3

.PHONY: clean

clean:
	rm -rf problema1 problema2 problema3
