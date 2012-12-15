#include <stdlib.h>
#include <stdio.h>

#include "naive.h"
#include "naive_mult.h"
#include "matrixio.h"


// Cette fonction ne libère aucune mémoire qui lui passée
// (à part les valculs intermediaires)
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
  }

  return cur_product; 
}


int main (int argc, char ** argv)
{
  int mat_count = -1;

  scanf ("%d", &mat_count);
  return 0;
}

