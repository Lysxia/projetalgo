CC=gcc
SRC= matrixio.c naive.c extracted.c strassen.c
HDR= matrixio.h naive.h extracted.h strassen.h
EXEC=strassen
CFLAGS=-D MULT_NAIVE=1 -O2


# Variables dépendant des cibles
strassen1: CFLAGS=-D MULT_NAIVE=1 -O2 -Wno-unused-result 
strassen2: CFLAGS=-D MULT_NAIVE=0 -D OSTRASSEN -D STOP=50 -O2 -Wno-unused-result

strassen1: EXEC=strassen1
strassen2: EXEC=strassen2


# Strassen1 et 2 ne servent qu'à définir des variables particulières
strassen1: strassen
strassen2: strassen


strassen: $(SRC) $(HDR) main.c main.h
	$(CC) $(CFLAGS) $(SRC) main.c -o $(EXEC)


1.100: rand2 strassen1
	./rand2 100 100 100 | ./strassen1

1.1000: rand2 strassen1
	./rand2 1000 1000 1000 | ./strassen1

1.3000: rand2 strassen1
	./rand2 3000 3000 3000 | ./strassen1

2.%: rand2 strassen2
	./rand2 $* $* $* | ./strassen2

2.100: rand2 strassen2
	./rand2 100 100 100 | ./strassen2

2.1000: rand2 strassen2
	./rand2 1000 1000 1000 | ./strassen2

2.3000: rand2 strassen2
	./rand2 3000 3000 3000 | ./strassen2

rand2: randmatrices.c
	gcc randmatrices.c -o rand2


paren:
	g++ parenthesization.c


# Général
clean:
	rm -f *\~ *.o
