CC=gcc
SRC= matrixio.c naive_mult.c extracted.c strassen.c
HDR= matrixio.h naive_mult.h extracted.h strassen.h
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

# ____.:Build:.____
# Programme principal
strassen: $(SRC) $(HDR) main.c main.h
	$(CC) $(CFLAGS) $(SRC) main.c -o $(EXEC)


# Programme de génération de 2 matrices
rand2: randmatrices.c
	gcc randmatrices.c -o rand2



# ____.:Tests:.____
1.%: rand2 strassen1
	./rand2 $* $* $* | ./strassen1

2.%: rand2 strassen2
	./rand2 $* $* $* | ./strassen2



paren:
	g++ parenthesization.c


# ____.:Utils:.____
clean:
	rm -f *\~ *.o
