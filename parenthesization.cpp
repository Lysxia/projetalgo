#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "operation_tree.h"

#define min(a,b) (a < b ? a : b)


typedef uint32_t mat_size_t;
typedef uint32_t cost_t;


// Tableau d'"op_tree" dans lequel on va préallouer tout l'arbre : TODO : cleaner en sortie
static op_tree_t * op_tree = 0;
static int next_free_node = 0; // Indique le prochain noeud non utilisé, pour ce même arbre


cost_t get_cost (mat_size_t m, mat_size_t n, mat_size_t o)
{
  return m * n * o; // TODO
}


// Simples macro "de confort" pour les 2 fonctions suivantes
#define cost(i,j) c[(j) + (i)*term_c]
#define cut(i,j) c[(j) + (i)*term_c + 1]

op_tree_t * build_tree (int * result_array, int term_c)
{
  
  return 0; // TODO
}


int /* ← TODO */ get_optimal_product (int term_c, mat_size_t * sizes)
{
  int * c = (int *) malloc (2 * term_c * term_c * sizeof (int));
  op_tree_t * result = 0;
  

  for (int i = 0; i < term_c; i++)
    cost(i,i) = 0;
  
  
  // sz : taille du sous-produit considéré (- 1)
  for (int sz = 1; sz < term_c; sz++)
  {
    // start : indice de la première matrice du sous-produit
    for (int start = 0; start < term_c - sz /* Idem */; start++)
    {
      cost_t min_cost = 0xFFFFFFFF;
      int min_cut = -1;
      
      for (int cut = 0, cur = 0; cut < sz; cut++)
      {
	cur = cost (start, start + cut) + cost(start + cut + 1, start + sz) 
	  + get_cost (sizes[start], sizes[start + cut + 1], sizes[start + sz + 1]); 
	// Attention : quand c'est un b, il faut bien mettre + 1

        if (cur < min_cost)
        {
	  min_cost = cur;
	  min_cut = cut;
	}
      }

      cost(start, start + sz) = min_cost;
      cut(start, start + sz) = min_cut;
      printf("%d ", min_cut); /* FIXME : debug */
    }
    
    printf("\n"); /* FIXME : debug */
  }

  // Parcours inverse pour la construction de l'arbre
  result = build_tree (c, term_c);

  free (c);

  return cut(1, term_c - 1);
}

#undef cost
#undef cut



void clean_tree ()
{
  free (op_tree);
}

// Main uniquement pour le test
int main () 
{
  // (10 * 100) * (100 * 5) * (5 * 50) -> optimal : de gauche à droite
  //mat_size_t sizes [] = {10, 100, 5, 50};
  mat_size_t sizes [] = {10, 100, 80, 5, 50};
  //mat_size_t sizes [] = {10, 100, 5, 50, 80, 1, 50};

  int s = sizeof(sizes)/sizeof(mat_size_t);

  get_optimal_product (s, sizes);

  for (int i = 0; i < s - 1; i++)
    printf("(%d|%d) ", sizes[i], sizes[i+1]);

  printf("\n");
}
