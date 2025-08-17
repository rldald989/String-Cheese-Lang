HEADER	= 
OUT	= strc
CC	 = g++
FLAGS	 = -g -std=17 -c -Wall

all: main strc.o

main: strc.o
	g++ bin/strc.o -o bin/strc

strc.o: src/main.cpp
	g++ -c src/main.cpp -o bin/strc.o

clean:
	Remove-Item $(OBJS) $(OUT)

.PHONY run:
	make clean
	make
	cls
	./strc