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
