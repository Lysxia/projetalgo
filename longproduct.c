#include<stdio.h>
#include<stdlib.h>
#include"multiply.h"
#include"parenthesization.h"

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
	  if (a!=s[i])
	}
    }
    else if (argc==2)
    {

    }
    else
    {
	printf("Too many arguments.");
	return 1;
    }

    return 0;
}

int eq_string(char* s1, char* s2)
{
    int i=0;
    while (s1[i]==s2[i]&&s1[i]!='\0'&&s2[i]!='\0')
	i++;
    return s1[i]==s2[i];
}
