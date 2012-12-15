#include<stdio.h>
#include<stdlib.h>

#include "randpi.h"

#define R rand()%(max-min)+min

int* randmatrix(int m, int n)
{
    int i, *a=malloc(m*n*sizeof(int));
    for (i=0 ; i<m*n ; i++)
	a[i]=rand();
    return a;
}

//Rand Pi (Produit) de matrices, de tailles min à max exclus
int** randmatrices(int n_mat, int** s, int min, int max)
{
    if (min<1)
	min=1;
    if (max<min+1)
	max=min+1;
    srand(max*min);
    int m, n, *a=malloc(n_mat*sizeof(int*));
    int *t=malloc((n_mat+1)*sizeof(int));

    t[0]=R;
    for (i=0 ; i<n_mat ; i++)
    {
	t[i+1]=R;
	m[i]=randmatrix(t[i],t[i+1]);
    }
    
    *s=t;

    return m;
}
