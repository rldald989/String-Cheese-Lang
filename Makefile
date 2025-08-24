OUT	= strc

all: main

main: strc.o Logger.o
	g++ -std=c++20 bin/strc.o bin/Logger.o -o bin/strc

strc.o: src/main.cpp
	g++ -std=c++20 -c src/main.cpp -o bin/strc.o

Logger.o: src/Logger.cpp
	g++ -std=c++20 -c src/Logger.cpp -o bin/Logger.o

clean:
	Remove-Item $(OBJS) $(OUT)

.PHONY run:
	make clean
	make
	cls
	./strc