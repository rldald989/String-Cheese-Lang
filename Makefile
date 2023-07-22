OBJS	= src/main.o
SOURCE	= src/main.cpp
HEADER	= 
OUT	= strc
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)

.PHONY run:
	make clean
	make
	cls
	./strc