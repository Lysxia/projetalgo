#include<stdio.h>
#include<stdlib.h>
#include"multiply.h"
#include"parenthesization.h"

int main(int argc, char** argv)
{
    int n_mat, **m, a, b;
    mat_size_t *s;
/*
    if (argc==1)
    {
        scanf("%d ", n_mat)
    }
    else if (argc==2)
    {
    }
    else
    {
	printf("Too many arguments.");
	return 1;
    }*/
    mat_size_t k;
    scanf("%u",&k);
    printf("%u",k);
    return 0;
}

int eq_string(char* s1, char* s2)
{
    int i=0;
    while (s1[i]==s2[i]&&s1[i]!='\0'&&s2[i]!='\0')
	i++;
    return s1[i]==s2[i];
}
