.PHONY: all lab1 lab2 lab3 lab4 lab5 lab6 lab7 lab8 lab9 lab10 sem2 sem3 sapd-sem3 sapd1 clean dm1 sapd4 sapd21
# if [ "${VERSION}" \> "4.7" ]; then STD="-std=c++11"; else STD="-std=c++0x"; fi;
all:
	make clean
	make sem2
	make sem3

prog-sem2:
	make clean
	make lab1
	make lab2
	make lab3
	make lab4
	make lab5

prog-sem3:
	make lab6
	make lab7
	make lab8
	make lab9
	make lab10

sapd-sem3:
	make sapd1
	make sapd2
	make sapd3
	make sapd4

sapd-sem4:
	make sapd21

sapd-test:
	make test-sapd1

sem2:
	make prog-sem2
	make dm1

sem3:
	make prog-sem3
	make sapd-sem3

sapd1:
	g++ -g -std=c++11 ./sapd/lab1/lab1.cpp -o ./bin/sapd1

sapd1-test:
	make clean
	make sapd1
	touch ./report/sapd1.md
	echo "10" | ./bin/sapd1 > ./report/sapd1.md
	echo "50" | ./bin/sapd1 >> ./report/sapd1.md
	echo "100" | ./bin/sapd1 >> ./report/sapd1.md
	echo "200" | ./bin/sapd1 >> ./report/sapd1.md


sapd2:
	g++ -g -std=c++11 ./sapd/lab2/lab2.cpp -o ./bin/sapd2

sapd2-test:
	make clean
	make sapd2
	touch ./report/sapd2.md
	echo "10" | ./bin/sapd2 > ./report/sapd2.md
	echo "50" | ./bin/sapd2 >> ./report/sapd2.md
	echo "100" | ./bin/sapd2 >> ./report/sapd2.md
	echo "200" | ./bin/sapd2 >> ./report/sapd2.md

sapd3:
	g++ -g -std=c++11 ./sapd/lab3/lab3.cpp -o ./bin/sapd3

sapd3-test:
	make clean
	make sapd3
	touch ./report/sapd3.md
	echo "10" | ./bin/sapd3 > ./report/sapd3.md
	echo "50" | ./bin/sapd3 >> ./report/sapd3.md
	echo "100" | ./bin/sapd3 >> ./report/sapd3.md
	echo "200" | ./bin/sapd3 >> ./report/sapd3.md

sapd4:
	g++ ./sapd/lab4/lab4.cpp -g -std=c++11 -o ./bin/sapd4

sapd4-test:
	make clean
	make sapd4
	touch ./report/sapd4.md
	echo -e "1\n10\n2\n4\n" | ./bin/sapd4 > ./report/sapd4.md
	echo -e "1\n50\n2\n4\n" | ./bin/sapd4 >> ./report/sapd4.md
	echo -e "1\n100\n2\n4\n" | ./bin/sapd4 >> ./report/sapd4.md
	echo -e "1\n200\n2\n4\n" | ./bin/sapd4 >> ./report/sapd4.md


sapd5:
	g++ ./sapd/lab5/lab5.cpp -o ./bin/sapd5

sapd21:
	g++ ./sapd/lab21/lab21.cpp -g -std=c++11 -o ./bin/sapd21


lab1:
	g++ ./programming/lab1/lab1.cpp -o ./bin/lab1

lab2:
	g++ ./programming/lab2/lab2.cpp -o ./bin/lab2
	g++ ./programming/lab2/lab22.cpp -o ./bin/lab22

lab3:
	g++ ./programming/lab3/lab31.cpp -o ./bin/lab31
	g++ ./programming/lab3/lab32.cpp -o ./bin/lab32
	g++ ./programming/lab3/lab33.cpp -o ./bin/lab33

lab4:
	g++ ./programming/lab4/lab4.cpp -o ./bin/lab4

lab5:
	g++ ./programming/lab5/lab5.cpp -o ./bin/lab5

lab6:
	g++ ./programming/lab6/lab6.cpp -o ./bin/lab6

lab7:
	g++ ./programming/lab7/lab7.cpp -o ./bin/lab7


lab8:
	g++ ./programming/lab8/lab8.cpp -o ./bin/lab8

lab9:
	g++ ./programming/lab9/lab9.cpp -o ./bin/lab9

lab10:
	g++ ./programming/lab10/lab10.cpp -std=c++11 -o ./bin/lab10

dm1:
	g++ ./discrete_mathematics/dm1/dm1.cpp -o ./bin/dm1 -std=c++11

clean:
	rm -rf ./bin
	mkdir ./bin
	rm -rf ./report
	mkdir ./report
