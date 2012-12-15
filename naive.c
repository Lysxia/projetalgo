#include <stdlib.h>
#include <stdio.h>

#include "naive.h"
#include "naive_mult.h"
#include "matrixio.h"


int main (int argc, char ** argv)
{
  int mat_count;
  int **matrices;
  int *sizes;
  int *result;

  if (argc==1)
    matrices = read_matrices (&sizes, &mat_count);
  else if (argc==2)
  {
      FILE *f;
      if (NULL==(f=fopen(argv[1],"r")))
      {
	  printf("Failed to open file '%s'\n",argv[1]);
	  return 1;
      }
      matrices = fread_matrices (f,&sizes,&mat_count);
  }

  if (matrices == NULL)
  {
    printf("Error while reading matrices...\n");
    return 1;
  }

  result = naive_product (matrices, sizes, mat_count);

  print_matrix (result, sizes[0], sizes[mat_count]);
  
  return 0;
}

