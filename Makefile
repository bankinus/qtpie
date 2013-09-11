CC=g++

testreihie: testreihe.cpp
	$(CC) -std=c++11 -pthread -o testreihe testreihe.cpp
