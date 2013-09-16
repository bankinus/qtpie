CC=g++

testreihe: testreihe.cpp
	$(CC) -std=c++11 -pthread -o vergleich testreihe.cpp -lrt -O3
debug: testreihe.cpp
	$(CC) -std=c++11 -pthread -o vergleich testreihe.cpp -lrt -g
msdebug: mstest.cpp
	$(CC) -std=c++11 -pthread -o debug mstest.cpp -lrt -g
tmdebug: tlmutex.cpp
	$(CC) -std=c++11 -pthread -o debug tlmutex.cpp -lrt -g
