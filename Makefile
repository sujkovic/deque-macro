all: assignment1

assignment1: test.o
	g++ -o assignment1 test.o

test.o:
	g++ -c -g -ldl test.cpp

clean:
	rm -f assignment1 *.o