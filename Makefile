OBJ= matrixio.o naive.o strassen.o
# Variables dépendant des cibles
strassen1: CFLAGS=-D PRINT=false -D MULT_NAIVE=true -D OPTIM=1 -D OPTIM2=1\
	-D OPTIM3=1 -D STOP=50 -O2
strassen2: CFLAGS=-D PRINT=false -D MULT_NAIVE=false -D OPTIM=1 -D OPTIM2=1\
	-D OPTIM3=2 -D STOP=50 -O2

strassen1: EXEC=strassen1
strassen2: EXEC=strassen2



# Strassen1 et 2 ne servent qu'à définir des variables particulières
strassen1: strassen
strassen2: strassen


strassen: $(OBJ) main.o
	g++ $(CFLAGS) $(OBJ) main.o -o $(EXEC)


%.o: %.cpp %.h
	g++ $(CFLAGS) $< -c

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
