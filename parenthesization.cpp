#define  __STDC_LIMIT_MACROS
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define min(a,b) (a < b ? a : b)
// ceil(m/2^k)
#define crazy(m,k) (((m)>>(k))+(((m)&((1<<(k))-1))!=0))

typedef uint32_t mat_size_t;
typedef uint64_t cost_t;


// Tableau dans lequel on stocke les coupures pour les produits successifs
// Elles définissent un arbre binaire, stocké dans l'ordre préfixe
static int * op_cuts = 0;
static int next_free_node = 0; // Indique le prochain noeud non utilisé, pour ce même arbre


int pow7(int n)
{
  if (n==0)
    return 1;
  else
  {
    int k;
    k=pow7(n>>1);
    return (n&1)?k*k*7:k*k;
  }
}

cost_t get_cost (mat_size_t m, mat_size_t n, mat_size_t o)
{
#ifdef REAL_COST
  //log2(v) in few op
  int v=min(m,min(n,o)), r, shift;

  r =     (v > 0xFFFF) << 4;
  v >>= r;
  shift = (v > 0xFF  ) << 3;
  v >>= shift;
  r |= shift;
  shift = (v > 0xF   ) << 2;
  v >>= shift;
  r |= shift;
  shift = (v > 0x3   ) << 1;
  v >>= shift;
  r |= shift;
  r |= (v >> 1);

  //cout de Strassen
  return pow7(v)*crazy(m,v)*crazy(n,v)*crazy(o,v);
#else
  return m * n * o;
#endif
}


// Simples macro "de confort" pour les 2 fonctions suivantes
#define cost(i,j) c[((j) + (i)*term_c) << 1]
#define cut(i,j) c[(((j) + (i)*term_c) << 1) + 1]


void _bt (int * c, int term_c, int begin, int end)
{
  // On renvoie une coupure même pour le produit de 2 matrices
  if (end - begin >= 1)
  {
    int cur_cut = cut(begin, end); 
    
    op_cuts [next_free_node++] = cur_cut + 1; // On indice les coupures à partir de 1
    // (alors que le tableau de resultats les indice à partir de 0)
    
    _bt (c, term_c, begin, begin + cur_cut);
    _bt (c, term_c, begin + cur_cut + 1, end);
  }
}

void build_tree (int * result_array, int term_c)
{
  _bt (result_array, term_c, 0, term_c - 1); 
}


int * get_optimal_product (int term_c, mat_size_t * sizes)
{
  term_c -= 1; // Le dernier élement du tableau correspond au dernier "b"

  int * c = (int *) malloc (2 * term_c * term_c * sizeof (int));
  
  for (int i = 0; i < term_c; i++)
    cost(i,i) = 0;
  
  
  // sz : taille du sous-produit considéré - 1
  for (int sz = 1; sz < term_c; sz++)
  {
    // start : indice de la première matrice du sous-produit
    for (int start = 0; start < term_c - sz; start++)
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
      printf("%d [%d %d]", min_cut+1, start, sz); /* FIXME : debug */
    }
    
    printf("\n"); /* FIXME : debug */
  }

  // Parcours inverse pour la construction de l'arbre
  op_cuts = (int*) malloc ((term_c - 1) * sizeof(int));
  build_tree (c, term_c);

  free (c);

  return op_cuts;
}

#undef cost
#undef cut



void clean_tree ()
{
  free (op_cuts);
}

// Main uniquement pour le test
int main () 
{
  // (10 * 100) * (100 * 5) * (5 * 50) -> optimal : de gauche à droite
  //mat_size_t sizes [] = {10, 100, 5, 50};
  //mat_size_t sizes [] = {10, 100, 80, 5, 50};
  //mat_size_t sizes [] = {10, 100, 5, 50, 80, 1, 50};
  mat_size_t sizes [] = {100, 75, 50, 5, 800, 125, 50, 80, 50};

  int s = sizeof(sizes)/sizeof(mat_size_t);

  get_optimal_product (s, sizes);

  for (int i = 0; i < s - 1; i++)
    printf("(%d|%d) ", sizes[i], sizes[i+1]);

  printf("\n");

  printf("Result:\n");
  for (int i = 0; i < s - 2; i++) printf("%d ", op_cuts[i]);
  printf("\n");

  clean_tree ();
  return 0;
}
