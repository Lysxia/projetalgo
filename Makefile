OBJ= matrixio.o naive.o strassen.o main.o

strassen: $(OBJ)
	g++ -O2 $(OBJ) -o strassen

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

rand2: randmatrices.c
	gcc randmatrices.c -o rand2


paren:
	g++ parenthesization.cpp


# Général
clean:
	rm -f *\~ *.o *.gch

all:
	g++ -O2 strassen.cpp -o strassen
