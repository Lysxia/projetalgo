#define  __STDC_LIMIT_MACROS
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define min(a,b) (a < b ? a : b)


typedef uint32_t mat_size_t;
typedef uint64_t cost_t;


// Tableau dans lequel on stocke les coupures pour les produits successifs
static int * op_tree = 0;
static int next_free_node = 0; // Indique le prochain noeud non utilisé, pour ce même arbre


cost_t get_cost (mat_size_t m, mat_size_t n, mat_size_t o)
{
#ifdef REAL_COST
  return ;
#else
  return m * n * o; // TODO
#endif
}


// Simples macro "de confort" pour les 2 fonctions suivantes
#define cost(i,j) c[(j) + (i)*term_c]
#define cut(i,j) c[(j) + (i)*term_c + 1]

void _bt (int * res_array, int term_c, int begin, int end)
{
  if (end - begin > 1);
  next_free_node++;
}

void build_tree (int * result_array, int term_c)
{
  _bt (result_array, term_c, 0, term_c- 1); 
}


int * get_optimal_product (int term_c, mat_size_t * sizes)
{
  int * c = (int *) malloc (2 * term_c * term_c * sizeof (int));
  
  term_c -= 1; // Le dernier élement du tableau correspond au dernier "b"

  for (int i = 0; i < term_c; i++)
    cost(i,i) = 0;
  
  
  // sz : taille du sous-produit considéré (- 1)
  for (int sz = 1; sz < term_c; sz++)
  {
    // start : indice de la première matrice du sous-produit
    for (int start = 0; start < term_c - sz /* Idem */; start++)
    {
      cost_t min_cost = UINT64_MAX;
      int min_cut = -1;
      
      for (int cut = 0, cur_cost = 0; cut < sz; cut++)
      {
	cur_cost = cost (start, start + cut) + cost(start + cut + 1, start + sz) 
	  + get_cost (sizes[start], sizes[start + cut + 1], sizes[start + sz + 1]); 
	// Attention : quand c'est un b, il faut bien mettre + 1

        if (cur_cost < min_cost)
        {
	  min_cost = cur_cost;
	  min_cut = cut;
	}
      }

      cost(start, start + sz) = min_cost;
      cut(start, start + sz) = min_cut;
      printf("%d ", min_cut+1); /* FIXME : debug */
    }
    
    printf("\n"); /* FIXME : debug */
  }

  // Parcours inverse pour la construction de l'arbre
  op_tree = (int*) malloc ((term_c - 1) * sizeof(int));
  build_tree (c, term_c);

  free (c);

  return op_tree;
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
  //mat_size_t sizes [] = {10, 100, 80, 5, 50};
  mat_size_t sizes [] = {10, 100, 5, 50, 80, 1, 50};

  int s = sizeof(sizes)/sizeof(mat_size_t);

  get_optimal_product (s, sizes);

  for (int i = 0; i < s - 1; i++)
    printf("(%d|%d) ", sizes[i], sizes[i+1]);

  printf("\n");

  clean_tree ();
  return 0;
}
