CC=g++

testreihe: testreihe.cpp
	$(CC) -std=c++11 -pthread -o vergleich testreihe.cpp -lrt -O3
debug: testreihe.cpp
	$(CC) -std=c++11 -pthread -o vergleich testreihe.cpp -lrt -g
