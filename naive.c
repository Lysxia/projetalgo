#include <stdlib.h>
#include <stdio.h>

#include "naive.h"
#include "naive_mult.h"
#include "matrixio.h"


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


int main (int argc, char ** argv)
{
  int mat_count = -1;
  int ** matrices = NULL;
  int * sizes = NULL;
  int * result = NULL;

  matrices = read_matrices (&sizes, &mat_count);

  if (matrices == NULL || sizes == NULL)
  {
    printf("Error while reading matrices...\n");
    return 1;
  }

  result = naive_product (matrices, sizes, mat_count);

  print_matrix (result, sizes[0], sizes[mat_count]);
  
  return 0;
}

