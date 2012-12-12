#include <stdint.h>
#include <stdlib.h>

#define min(a,b) (a < b ? a : b)


typedef uint32_t size_t;
typedef uint32_t cost_t;

cost_t get_cost (size_t m, size_t n, size_t o)
{
  return m * n * o; // TODO
}


int /* ← TODO */ get_optimal_product (int term_c, size_t * sizes)
{
#define cost(i,j) c[j + i * term_c]
#define begin {
#define end }

  int * c = (int *) malloc (term_c * term_c * sizeof (int));
  
  // On incrémente directement les pointeurs, plutôt que des indices
  for (int * i = c; i < c + term_c * (term_c + 1); i += term_c + 1)
    *i = 0;
  
  
  // Utilisation directe des pointeurs ?
  for (int j = 0; j < term_c - 1 /* Il semble que c'est bien < n - 1 */; j++)
    for (int i = 0; i < term_c - j /* Idem */; i++)
    begin
      cost_t min = 0xFFFFFFFF;
      int min_k = -1;
      for (int k = 0, cur = 0; k < j /* Verifier */; k++)
      begin
	cur = cost (i, i+k) + cost(i+k+1, i+j) + get_cost (1, 2, 3 /* FIXME : a finir */);
        if (cur < min)
	begin
	  min = cur;
	  min_k = k;
	end
      end

      cost(i, i+j) = min;
	// TODO : peut-être garder le min_k
	
      
    end

  return 2;

#undef cost
#undef begin
#undef end
}
