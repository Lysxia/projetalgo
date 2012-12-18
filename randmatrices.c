#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv)
{
    int m=0,n=0,o=0;
    int i;
    if (argc==1)
    {
	printf("Matrix dimensions ? (3 integers) :");
	scanf("%d %d %d ", &m, &n, &o);
    }
    else if (argc==4)
    {
	int *s[3]={&m,&n,&o}, j;

	for (j=0 ; j<3 ; j++)
	{
	    i = 0;
	    while (argv[j+1][i]!='\0')
	    {
		if (argv[j+1][i]>='0' && argv[j+1][i]<='9')
		    *(s[j]) = 10* *(s[j])+(argv[j+1][i++]-'0');
		else
		{
		    printf("Not a number.");
		    return 1;
		}
	    }
	}
    }
    else
    {
	printf("3 integer command line arguments expected.");
	return 1;
    }

    printf("%d %d\n", m, n);

    srand(m*n*o);
    for (i=0 ; i<m*n ; i++)
        printf(((i+1)%n)?"%d ":"%d\n",rand()%10);
    printf("%d %d\n", n, o);
    for (i=0 ; i<n*o ; i++)
        printf(((i+1)%o)?"%d ":"%d\n",rand()%10);

    return 0;
}
