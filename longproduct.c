#include<stdio.h>
#include<stdlib.h>

#include "matrixio.h"
#include "multiply.h"
#include "parenthesization.h"

int main(int argc, char** argv)
{
    int n_mat; // Nb matrices
    int **m;   // matrix list
    int *s;    // matrix size list

    if (argc==1)
    {
	m=read_matrices(&s,&n_mat);
    }
    else if (argc==2)
    {
	FILE *f=fopen(argv[1],"r");
	if (f==NULL)
	{
	    printf("Failed to open file '%s'\n",argv[1]);
	    return 1;
	}
	m=fread_matrices(f,&s,&n_mat);
    }
    else
    {
	printf("Too many arguments.\n");
	return 1;
    }

    int *order=get_optimal_product(n_mat,s);
    int *product=orderedmult(m,s,order,n_mat);

    print_paren(order,s,n_mat-1);
    print_matrix(product,s[0],s[n_mat]);

    return 0;
}

int eq_string(char* s1, char* s2)
{
    int i=0;
    while (s1[i]==s2[i]&&s1[i]!='\0'&&s2[i]!='\0')
	i++;
    return s1[i]==s2[i];
}
