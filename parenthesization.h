#ifndef PARENTH_H
#define PARENTH_H

#define  __STDC_LIMIT_MACROS
#include <stdint.h>

typedef uint64_t cost_t;

int* get_optimal_product(int, int* sizes);
void build_tree (int*,int);
void clean_tree ();
void _bt (int*,int, int,int);

cost_t get_cost (int, int, int);

cost_t pow7(int);

#endif
