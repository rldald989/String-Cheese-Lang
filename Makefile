HEADER	= 
OUT	= strc
CC	 = g++
FLAGS	 = -g -std=17 -c -Wall

all: main

main: strc.o Logger.o
	g++ bin/strc.o bin/Logger.o -o bin/strc

strc.o: src/main.cpp
	g++ -c src/main.cpp -o bin/strc.o

Logger.o: src/Logger.cpp
	g++ -c src/Logger.cpp -o bin/Logger.o

clean:
	Remove-Item $(OBJS) $(OUT)

.PHONY run:
	make clean
	make
	cls
	./strc