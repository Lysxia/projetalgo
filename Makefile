CC=gcc
SRC=matrixio.c naive.c extracted.c strassen.c
HDR=matrixio.h naive.h extracted.h strassen.h
PAR=parenthesization.c
PHD=parenthesization.h
EXECSTR=strassen
EXECLPD=lpd
CFLAGS=-D MULT_NAIVE=1 -O2 -Wno-unused-result 
COPTFLAG=-D MULT_NAIVE=0 -D OSTRASSEN -D STOP=50 -O2 -Wno-unused-result


# Variables dépendant des cibles
strassen2: CFLAGS=$(COPTFLAGS)

strassen1: EXECSTR=strassen1
strassen2: EXECSTR=strassen2

# Strassen1 et 2 ne servent qu'à définir des variables particulières
strassen1: strassen
strassen2: strassen

# lpd:longproduct, effectue le produit de n matrices
lpd1: EXECLPD=lpd1
lpd2: EXECLPD=lpd2 CFLAGS=$(COPTFLAGS)

lpd1: lpd
lpd2: lpd

# ____.:Build:.____
# Programme principal
strassen: $(SRC) $(HDR) main.c main.h
	$(CC) $(CFLAGS) $(SRC) main.c -o $(EXECSTR)

# Multiplication d'une suite de matrices
lpd: $(SRC) $(HDR) $(PAR) $(PHD) longproduct.c longproduct.h
	$(CC) $(CFLAGS) $(SRC) $(PAR) longproduct.c -o $(EXECLPD)


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
