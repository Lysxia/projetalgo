#include<stdio.h>
#include<stdlib.h>
#include"matrixio.h"


// Fonctions de lecture et affichage, représentation brute
int * read_matrix (int m, int n)
{
  int * r;
  if (0 == (r = (int *) malloc (m*n*sizeof(int))))
      return 0;

  for (int i = 0; i < m * n; i++)
    scanf("%d ", r + i);
  
  return r;
}

void print_matrix (int * A, int m, int n)
{
  printf ("Matrix %d %d :\n", m, n);

  for (int i = 0; i < m * n; i++)
    printf((i + 1) % n ? "%d " : "%d\n", A[i]);
}

// Représentation sous-matrice
void print_extr(int * A, int m, int n, int w)
{
#if PRINT
    printf("Matrix %d %d :\n", m, n);

    for (int i = 0 ; i<m ; i++)
	for (int j = 0 ; j<n ; j++)
	    printf((j==n-1)?"%d\n":"%d ",A[j+i*w]);
#endif
}
