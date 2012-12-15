#include<stdio.h>
#include<stdlib.h>
#include"matrixio.h"


// Fonctions de lecture et affichage, représentation brute
int * read_matrix (int* m, int* n)
{
  int * r;
  scanf("%d %d",m,n);
  if (0 == (r = (int *) malloc (*m**n*sizeof(int))))
      return 0;

  for (int i = 0; i < *m * *n; i++)
    scanf("%d ", r + i);
  
  return r;
}

void print_matrix (int * A, int m, int n)
{
  printf ("Matrix %d %d :\n", m, n);

  for (int i = 0; i < m * n; i++)
    printf((i + 1) % n ? "%d " : "%d\n", A[i]);
}

// Affiche le parenthésage représenté par tree (arbre de coupures)
void print_paren(int* tree, int n)
{
    if (!n)
    {
	printf("%d\n",0);
	return;
    }

    _print_paren(tree,n,0);
    printf("\n");
    return;
}


/* Fonctions auxiliaires */

// Représentation sous-matrice
void print_extr(int * A, int m, int n, int w)
{
#ifdef PRINT
    printf("Matrix %d %d :\n", m, n);

    for (int i = 0 ; i<m ; i++)
	for (int j = 0 ; j<n ; j++)
	    printf((j==n-1)?"%d\n":"%d ",A[j+i*w]);
#endif
}

void _print_paren(int* tree, int n, int i)
{
    if (tree[0]==1)
        printf("%d.",i);
    else
    {
        printf("(");
        _print_paren(tree,tree[0]-1,i);
	printf(").");
    }

    if (tree[0]==n)
	printf("%d",i+n);
    else
    {
	printf("(");
	_print_paren(tree+tree[0],n-tree[0],i+tree[0]);
	printf(")");
    }

    return;
}

bool matrix_equal(int* A, int* B, int m, int n)
{
    for (int i=0 ; i<m*n ; i++)
	if (!(A[i]==B[i]))
	    return false;
    return true;
}