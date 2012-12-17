#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "m2m.h"
#include "strassen.h"
#include "matrixio.h"
#include "naive_mult.h"

int main (int argn, char** argv)
{
#if 1

  int m, n, _n, o;
  int * A, * B, * C, * D;
  double t;
  
  if (NULL == (A = read_matrix(&m,&n)))
  {
      printf("Could not read 1st matrix.\n");
      return 1;
  }

  if (NULL == (B = read_matrix(&_n,&o)))
  {
      printf("Could not read 2nd matrix.\n");
      return 1;
  }
  else if (_n!=n)
  {
      printf("Matrix sizes not compatible.\n");
      return 1;
  }
#if PRINT
  print_matrix(A, m, n);
  print_matrix(B, n, o);
  printf("Strassen...\n");
#endif

  t=clock();
  if (NULL == (C = strassen(A,B,m,n,o)))
  {
      printf("Multiplication failed.\n");
      return 1;
  }

#if PRINT
  printf("Time : %.3fs\n",(clock()-t)/CLOCKS_PER_SEC);
  print_matrix(C, m, o);
#else
  printf((MULT_NAIVE)?"%.4f,":"%.4f\n",(clock()-t)/CLOCKS_PER_SEC);
#endif

#if PRINT
  printf("Naive mult...\n");
#endif

#if MULT_NAIVE==1
  t=clock();
  if (NULL == (D = naive_mult(A,B,m,n,o)))
  { 
      printf("Multiplication failed.\n");
      return 2;
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
#endif
  free(A);
  free(B);
  free(C);
  free(D);
  A=B=C=D=0;
#endif

  return 0;
}

