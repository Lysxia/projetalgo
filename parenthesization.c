#include <stdlib.h>
#include <stdio.h>
#include "parenthesization.h"

#define min(a,b) (a < b ? a : b)
// ceil(m/2^k)
#define crazy(m,k) (((m)>>(k))+(((m)&((1<<(k))-1))!=0))


// Simples macro "de confort" pour les 2 fonctions suivantes
#define cost(i,j) c[((j) + (i)*term_c) << 1]
#define cut(i,j) c[(((j) + (i)*term_c) << 1) + 1]


// Tableau dans lequel on stocke les coupures pour les produits successifs
// Elles définissent un arbre binaire, stocké dans l'ordre préfixe
static int *op_cuts = 0;
static int next_free_node = 0; // Indique le prochain noeud non utilisé, pour ce même arbre


int* get_optimal_product (int term_c, mat_size_t* sizes)
{
  //Le dernier élement du tableau sizes correspond à la deuxième
  //dimension de la dernière matrice
  //sizes est de taille term_c+1>=2

    int i, sz, start;
  int *c = malloc (2*term_c*term_c*sizeof (int));
  
  for (i = 0; i < term_c; i++)
    cost(i,i) = 0;
  
  
  // sz : taille du sous-produit considéré - 1
  for (sz = 1; sz < term_c; sz++)
  {
    // start : indice de la première matrice du sous-produit
    for (start = 0; start < term_c-sz; start++)
    {
      cost_t min_cost = UINT64_MAX;
      int cut, min_cut = -1;
      
      for (cut = 1, cur_cost = 0; cut <= sz; cut++)
      {
	cur_cost = cost (start, start+cut-1) + cost(start+cut, start+sz) 
	  + get_cost (sizes[start], sizes[start+cut], sizes[start+sz+1]); 
	// Attention : quand c'est un b, il faut bien mettre + 1

        if (cur_cost < min_cost)
        {
	  min_cost = cur_cost;
	  min_cut = cut;
	}
      }

      cost(start, start+sz) = min_cost;
      cut(start, start+sz) = min_cut;
    }
  }

  // Parcours inverse pour la construction de l'arbre
  op_cuts = malloc ((term_c-1) * sizeof(int));
  build_tree (c, term_c);

  free (c);

  return op_cuts;
}

void build_tree (int* result_array, int term_c)
{
  _bt (result_array, term_c, 0, term_c - 1); 
}

void _bt (int* c, int term_c, int begin, int end)
{
  // On renvoie une coupure même pour le produit de 2 matrices
  if (end-begin >= 1)
  {
    int cur_cut = cut(begin, end); 
    
    op_cuts [next_free_node++] = cur_cut; // On indice les coupures à partir de 1
    
    _bt (c, term_c, begin, begin+cur_cut);
    _bt (c, term_c, begin+cur_cut+1, end);
  }
}

#undef cost
#undef cut


cost_t get_cost (mat_size_t m, mat_size_t n, mat_size_t o)
{
#ifdef REAL_COST
  //log2(v) in few op
  int v=min(m,min(n,o)), r, shift;

  r =     (v>0xFFFF) << 4;
  v >>= r;
  shift = (v>0xFF  ) << 3;
  v >>= shift;
  r |= shift;
  shift = (v>0xF   ) << 2;
  v >>= shift;
  r |= shift;
  shift = (v>0x3   ) << 1;
  v >>= shift;
  r |= shift;
  r |= (v >> 1);

  //cout de Strassen
  return pow7(v)*crazy(m,v)*crazy(n,v)*crazy(o,v);
#else
  return m * n * o;
#endif
}


void clean_tree ()
{
  free (op_cuts);
}


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
