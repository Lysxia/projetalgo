#include <stdlib.h>
#include <stdio.h>

// Multiplication naîve
// A : m * n - B n * o
int* mult (int* A, int* B, int m, int n, int o)
{
  int *r = malloc (sizeof (int) * m * o);
  int i,j,k;
  
  for (i = 0; i < m; i++)
    for (j = 0; j < o; j++, r [i * o + j] = 0)
      for (k = 0; k < n; k++)
        r [i * o + j] += A [i * n + k] * B [k * o + j];

  return r;
}

