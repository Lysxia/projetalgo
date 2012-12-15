#include <stdlib.h>
#include <stdio.h>

#include "naive_mult.h"
#include "matrixio.h"

// Multiplication naîve
// A : m * n - B n * o
int* naive_mult (int* A, int* B, int m, int n, int o)
{
  int i,j,k;
  int *r = malloc (m*o*sizeof(int));
  if (r==NULL)
      return NULL;
  
  for (i=0 ; i<m ; i++)
    for (j=0 ; j<o ; j++)
    {
	r[i*o+j]=0;
      for (k=0; k < n; k++)
      {
        r[i*o+j] += A[i*n+k] * B[k*o+j];
      }
    }

  return r;
}

// Cette fonction ne libère aucune mémoire qui lui passée
// (à part lescalculs intermediaires)
// Il faut libérer son résultat une fois fini
int* naive_product (int** matrices, int * sizes, int term_count)
{
  int cur;
  int * previous_term, * cur_product;

  cur_product = matrices[0];

  for (cur = 1; cur < term_count; cur++)
  {
    previous_term = cur_product;
    
    cur_product = naive_mult (previous_term, matrices[cur], sizes[0], 
                              sizes[cur], sizes[cur+1]);
  
    if (cur > 1) // Il ne faut pas libérer la toute première matrice 
      // (terme du produit)
      free (previous_term);

    if (cur_product==NULL)
	return NULL;
  }

  return cur_product; 
}
