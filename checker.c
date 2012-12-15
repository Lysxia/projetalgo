#include <stdio.h>
#include <stdlib.h>

#include "checker.h"
#include "matrixio.h"
#include "multiply.h"
#include "naive_mult.h"
#include "randpi.h"

int main(int argc, char** argv)
{
    int **m, *s;
    int n, min, max;

    if (argc<4)
    {
	printf("Too few arguments\n");
	return 
    }
    sscanf(argv[1],"%d",&n);
    sscanf(argv)
}
