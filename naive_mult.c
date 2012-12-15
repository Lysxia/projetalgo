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

