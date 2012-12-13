#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"main.h"
#include"strassen.h"
#include"matrixio.h"
#include"naive.h"

int main (int argn, char** argv)
{

#if 0
    int m,n;
    int * M;
    scanf("%d %d ", &m, &n);

    if (0 == (M = read_matrix(m,n)))
    {
	printf("Could not read matrix.\n");
	return 1;
    }

    print_matrix(M, m, n);
#endif

#if 1

  int m,n,o;
  int *A, *B, *C, *D;
  float t;
  
  scanf("%d %d %d ", &m, &n, &o);

  if (0 == (A = read_matrix(m,n)))
  {
      printf("Could not read 1st matrix.\n");
      return 1;
  }

  if (0 == (B = read_matrix(n,o)))
  {
      printf("Could not read 2nd matrix.\n");
      return 1;
  }
#if PRINT
  print_matrix(A, m, n);
  print_matrix(B, n, o);
  printf("Strassen...\n");
#endif

  t=clock();
  if (0 == (C = strassen(A,B,m,n,o)))
  {
      printf("Multiplication failed.\n");
      return 1;
  }

#if PRINT
  printf("Time : %.3fs\n",(clock()-t)/CLOCKS_PER_SEC);
  print_matrix(C, m, o);
#else
  printf("%.4f,",(clock()-t)/CLOCKS_PER_SEC);
#endif

#if PRINT
  printf("Naive mult...\n");
#endif

  t=clock();
  if (0 == (D = mult(A,B,m,n,o)))
  { 
      printf("Multiplication failed.\n");
      return 1;
  }

#if PRINT
  printf("Time : %.3fs\n",(clock()-t)/CLOCKS_PER_SEC);
  print_matrix(D, m, o);

  if (matrix_equal(C,D,m,o))
      printf("1 : Okay\n");
  else printf("0 : Not Okay\n");
#else
  printf("%.4f\n",(clock()-t)/CLOCKS_PER_SEC);
#endif

  free(A);
  free(B);
  free(C);
  free(D);
  A=B=C=D=0;
#endif

#if 0
  int *A = 0, *B = 0, *C;
  int m, n, o;

  scanf("%d %d %d ", &m, &n, &o);
  A = read_matrix(m,n);
  B = read_matrix(n,o);
  C = mult(A,B,m,n,o);

  print_matrix(A,m,n);
  print_matrix(B,n,o);
  print_matrix(C,m,o);
#endif

#if 0
  while (scanf ("%d %d", &n, &o) != eof)
  {
    if (A == 0) 
    {
      A = read_matrix (n, o);
      print_matrix(A, n, o);
      m = n;
      n = o;
      continue;
    }
  
    B = read_matrix (n, o);
    C = mult (A, B, m, n, o);

    print_matrix (B, n, o); 
    
    print_matrix (C, m, o);
    free (A);
    free (B);
    A = C;
    n = o;
  }
#endif

  return 0;
}

bool matrix_equal(int* A, int* B, int m, int n)
{
    for (int i=0 ; i<m*n ; i++)
	if (!(A[i]==B[i]))
	    return false;
    return true;
}

