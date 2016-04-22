all:
	rm -rf ./bin
	mkdir ./bin
	g++ ./lab1/lab1.cpp -o ./bin/lab1.out;
	g++ ./lab2/lab2.cpp -o ./bin/lab2.out;

lab1:
	g++ ./lab1/lab1.cpp -o ./bin/lab1.out;

lab2:
	g++ ./lab2/lab2.cpp -o ./bin/lab2.out;

