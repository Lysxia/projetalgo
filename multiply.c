#include<stdio.h>
#include<stdlib.h>
#include"parenthesization.h"
#include"strassen.h"
#include"multiply.h"

// Optimally parenthesized multiplication
int* mult_opt(int** m, mat_size_t* s, int n_mat)
{
    int* order=get_optimal_product(n_mat,s);

    return orderedmult(m,s,order,n_mat);
}

int* orderedmult(int** m, mat_size_t* s, int* order, int n_mat)
{
    if (n_mat==1)
	return m[0];
    else
    {
	int* a=orderedmult(m,s,order+1,order[0]);
	int* b=orderedmult(m+order[0],
		s+order[0],order+order[0],n_mat-order[0]);
	return strassen(a,b,s[0],s[order[0]],s[n_mat]);
    }
}
