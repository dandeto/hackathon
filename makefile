all: tool

tool: main.o
	cd src; g++ -std=c++11 main.o -o tool
	cd src; mv tool ../

main.o:
	cd src; g++ main.cpp -c -std=c++11

.PHONY: all

clean:
	cd src; rm *.o tool