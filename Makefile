OBJ= matrixio.o naive.o strassen.o main.o

strassen: $(OBJ)
	g++ -O2 $(OBJ) -o strassen

%.o: %.cpp %.h
	g++ -O2 $< -c

test: test.txt
	./strassen < test.txt

rand2: randmatrices.c
	gcc randmatrices.c -o rand2

clean:
	rm -f *\~ *.o *.gch

all:
	g++ -O2 strassen.cpp -o strassen
