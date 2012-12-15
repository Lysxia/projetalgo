#include <stdlib.h>
#include <stdio.h>

#include "naive.h"
#include "naive_mult.h"
#include "matrixio.h"


// Cette fonction ne libère aucune mémoire qui lui passée
// (à part les valculs intermediaires)
int* naive_product (int** matrices, int * sizes, int term_count)
{
  int cur;
  int * previous_term, * cur_product;

  previous_term = matrices[0];

  for (cur = 1; cur < term_count; cur++)
  {
    
    cur_product = // produit
  
    if (i > 1) // Il ne faut pas libérer la toute première matrice 
      // (terme du produit)
      ; // TODO : freer le dernier termporaire
  }

  return NULL; // TODO
}


int main (int argc, char ** argv)
{
  int mat_count = -1;

  scanf ("%d", &mat_count);
  return 0;
}

