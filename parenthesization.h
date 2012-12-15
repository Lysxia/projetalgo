#ifndef PARENTH_H
#define PARENTH_H

#define  __STDC_LIMIT_MACROS
#include <stdint.h>

typedef uint32_t mat_size_t;
typedef uint64_t cost_t;

int* naiveorder(int);

int* get_optimal_product(int, mat_size_t* sizes);
void build_tree (int*,int);
void clean_tree ();
void _bt (int*,int, int,int);

cost_t get_cost (mat_size_t, mat_size_t, mat_size_t);

int pow7(int);

#endif
