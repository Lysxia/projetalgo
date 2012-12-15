#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "demo.h"
#include "matrixio.h"
#include "multiply.h"
#include "parenthesization.h"
#include "naive_mult.h"
#include "randpi.h"

int main(int argc, char** argv)
{
    int **m, *s;
    int n, min, max;

    int * op_order;
    int * strassen_res, * naive_res;

    double t;

    if (argc<4)
    {
	printf("Too few arguments\n");
	return 1;
    }
    
    // 1er argument : nombre de matrices
    sscanf(argv[1],"%d",&n);

    // 2e argument : min dimensions
    sscanf(argv[2], "%d", &min);

    // 3e arg : max dimensions
    sscanf(argv[3], "%d", &max);

    
    m = randmatrices(n, &s, min, max);

    t = clock();
    op_order = get_optimal_product (n, s);
    printf("Parenthesization time : %.3fs\n", (clock()-t)/CLOCKS_PER_SEC);

    print_paren(op_order, s, n - 1);


    t = clock();
    strassen_res = orderedmult (m, s, op_order, n);
    printf("Strassen time : %.3fs\n", (clock()-t)/CLOCKS_PER_SEC);


    // The following code is used only for the demo program (it computes the 
    // product and also checks if the product seems okay)
#ifdef CHECK_NAIVE
    t = clock();
    naive_res = naive_product (m, s, n);
    printf("Naive product time : %.3fs\n", (clock()-t)/CLOCKS_PER_SEC);

    if (!matrix_equal (strassen_res, naive_res, s[0], s[n]))
    {
      printf("Error : matrices are not equal\n");
      return 1;
    }
    else
      printf("Ok, result checked\n");
#endif

    // No need to free : we're exiting, the OS will get all the memory back...
    
    return 0;    
}
