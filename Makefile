.PHONY: all lab1 lab2 lab3 lab4 lab5 clean dm1
all:
	make clean
	make lab1
	make lab2
	make lab3
	make lab5
	make dm1

lab1:
	g++ ./lab1/lab1.cpp -o ./bin/lab1

lab2:
	g++ ./lab2/lab2.cpp -o ./bin/lab2
	g++ ./lab2/lab22.cpp -o ./bin/lab22

lab3:
	g++ ./lab3/lab31.cpp -o ./bin/lab31
	g++ ./lab3/lab32.cpp -o ./bin/lab32
	g++ ./lab3/lab33.cpp -o ./bin/lab33

lab4:
	g++ ./lab4/lab4.cpp -o ./bin/lab4

lab5:
	g++ ./lab5/lab5.cpp -o ./bin/lab5

dm1:
	g++ ./dm1/dm1.cpp -o ./bin/dm1

clean:
	rm -rf ./bin
	mkdir ./bin
