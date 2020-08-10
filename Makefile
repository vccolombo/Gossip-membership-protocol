CFLAGS = -g -std=c++11

all: main

main: main.o IPAddress.o
	g++ -o main main.o IPAddress.o ${CFLAGS}

main.o: main.cpp src/IPAddress.hpp
	g++ -c main.cpp ${CFLAGS}

IPAddress.o: src/IPAddress.cpp src/IPAddress.hpp
	g++ -c src/IPAddress.cpp ${CFLAGS}

clean:
	rm -rf main *.o