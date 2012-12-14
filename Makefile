OBJ= matrixio.o naive.o strassen.o

strassen: $(OBJ) main.o
	g++ -O2 const.h $(OBJ) main.o -o strassen
	

strassen1: const1.h $(OBJ) main.o
	cp const1.h const.h
	rm -f const.h

strassen2: const2.h $(OBJ) main.o
	cp const2.h const.h
	g++ -O2 const.h $(OBJ) main.o -o strassen2
	rm -f const.h

%.o: %.cpp %.h
	g++ -O2 $< -c

test: test.txt
	./strassen < test.txt

test100: rand2 strassen
	./rand2 100 100 100 | ./strassen

test1000: rand2 strassen
	./rand2 1000 1000 1000 | ./strassen

test2000: rand2 strassen
	./rand2 2000 2000 2000 | ./strassen

test3000: rand2 strassen
	./rand2 3000 3000 3000 | ./strassen

rand2: randmatrices.c
	gcc randmatrices.c -o rand2


paren:
	g++ parenthesization.cpp


# Général
clean:
	rm -f *\~ *.o *.gch

all:
	g++ -O2 strassen.cpp -o strassen
