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
    int _n, i;

    if (argc==1)
    {
        scanf("%d ", &n_mat);
	m=malloc(n_mat*sizeof(int*));
	s=malloc(n_mat*sizeof(int));
	for (i=0 ; i<n_mat ; i++)
	{
	  m[i]=read_matrix(s+i,s+i+1);
	  if (i>0&&_n!=s[i])
	  {
	      printf("Matrix sizes not compatible :");
	      printf("%ux%u, %ux%u",s[i-1],_n,s[i],s[i+1]);
	      return 1;
	  }
	  _n=s[i+1];
	}
    }
    else if (argc==2)
    {
        printf("Not implemented. Too many arguments.\n");
	return 1;
    }
    else
    {
	printf("Too many arguments.\n");
	return 1;
    }

    int *order=get_optimal_product(n_mat,s);
    int *product=orderedmult(m,s,order,n_mat);

    print_paren(order,n_mat-1);
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
