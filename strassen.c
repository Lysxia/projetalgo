#include<stdio.h>
#include<stdlib.h>
#include"strassen.h"

int next_pow_2(int n)
{
    int i=1;
    while (n>1)
    {
	i++;
	n>>=1;
    }
    return n<<i;
}

int M,N,P;

/* a[m][n], b[n][p] */
int* mult_matrix(int* a, int* b, int m, int n, int p)
{
    M=m;
    N=n;
    P=p;
    return rec_mult(a,b,next_pow_2(m),next_pow_2(n),next_pow_2(p),m,n,n,p,n,p);
}

/* a and b have zero coefficients outside of mc*nc, and are part of
 * matrices having Na and Nb columns */
int* add_matrix(int* a, int* b, int mc, int nc, int Na, int Nb)
{
    int i,j,Natimesj,Nbtimesj,nctimesj;
    int* c = malloc(mc*nc*sizeof(int));
    for (j=0,Natimesj=0,Nbtimesj=0,nctimesj=0 ; j<nc ; j++,Natimesj+=Na,Nbtimesj+=Nb,nctimesj+=nc)
	for (i=0 ; i<mc ; i++)
	    c[i+nctimesj] = a[i+Natimesj] + b[i+Nbtimesj];
    return c;
}

/* last six arguments indicate out of bounds coefficients */
int* rec_mult(int* a, int* b, int n, int m, int p, int na, int ma, int mb, int pb, int mA, int pB)
{
}
