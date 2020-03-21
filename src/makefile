all: tool

tool: main.o
	g++ -std=c++11 main.o -o tool

main.o: main.cpp
	g++ main.cpp -c -std=c++11

.PHONY: all

clean:
	rm *.o tool