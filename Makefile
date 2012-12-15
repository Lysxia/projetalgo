CC=gcc
# SRC/HDR : dépendances utilisées par tout le monde
SRC=randpi.c matrixio.c naive_mult.c extracted.c strassen.c
HDR=randpi.h matrixio.h naive_mult.h extracted.h strassen.h
PAR=parenthesization.c multiply.c
PHD=parenthesization.h multiply.h
EXECSTR=strassen
EXECLPD=lpd
EXECFM=fmult
EXECD=demo
CDEFFLAGS=-D MULT_NAIVE=1 -D REAL_COST -Wno-unused-result -O2
CFLAGS=$(CDEFFLAGS)
COPTFLAGS=-D MULT_NAIVE=0 -D REAL_COST -D OSTRASSEN -D STOP=50 -O2 -Wno-unused-result

default: rand2 strassen1 lpd1 naive fmult1 demo1
default: strassen2 lpd2 fmult2 demo2

# ____.:Build:.____
# Programme principal
strassen: $(SRC) $(HDR) m2m.c m2m.h
	$(CC) $(CFLAGS) $(SRC) m2m.c -o $(EXECSTR)

# Multiplication d'une suite de matrices
lpd: $(SRC) $(HDR) $(PAR) $(PHD) longproduct.c longproduct.h
	$(CC) $(CFLAGS) $(SRC) $(PAR) longproduct.c -o $(EXECLPD)

# Multiplication d'une suite de matrices par la méthode naïve
naive: $(SRC) $(HDR) naive.c naive.h
	$(CC) $(CFLAGS) $(SRC) naive.c -o naive

fmult: $(SRC) $(HDR) $(PAR) $(PHD) demo.h demo.c
	$(CC) $(CFLAGS) $(SRC) $(PAR) demo.c -o $(EXECFM)

demo: $(SRC) $(HDR) $(PAR) $(PHD) demo.h demo.c
	$(CC) $(CFLAGS) -D CHECK_NAIVE $(SRC) $(PAR) demo.c -o $(EXECD)


# Programme de génération de 2 matrices
rand2: randmatrices.c
	gcc randmatrices.c -o rand2


# Variables dépendant des cibles
strassen2: CFLAGS=$(COPTFLAGS)
strassenp: CFLAGS=$(CDEFFLAGS) -D PRINT


strassen1: EXECSTR=strassen1
strassen2: EXECSTR=strassen2
strassenp: EXECSTR=strassenp

# Strassen1 et 2 ne servent qu'à définir des variables particulières
strassen1: strassen
strassen2: strassen
strassenp: strassen

# lpd:longproduct, effectue le produit de n matrices
lpd1: EXECLPD=lpd1
lpd2: EXECLPD=lpd2
lpd2: CFLAGS=$(COPTFLAGS)

lpd1: lpd
lpd2: lpd

#
fmult1: EXECFM=fmult1
fmult2: EXECFM=fmult1
fmult2: CFLAGS=$(COPTFLAGS)

fmult1: fmult
fmult2: fmult

#
demo1: EXECFM=demo1
demo2: EXECFM=demo1
demo2: CFLAGS=$(COPTFLAGS)

demo1: demo
demo2: demo


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
