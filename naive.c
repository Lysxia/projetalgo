#include <stdlib.h>
#include <stdio.h>

#define eof EOF

// Multiplication naîve
// A : m * n - B n * o
int * mult (int * A, int * B, int m, int n, int o)
{
  int * r = malloc (sizeof (int) * m * o); // Bitch !
  
  for (int i = 0; i < m; i++)
    for (int j = 0; j < o; j++, r [i * o + j] = 0)
      for (int k = 0; k < n; k++)
        r [i * o + j] += A [i * n + k] * B [k * o + j];

  return r;
}


int * read_matrix (int m, int n)
{
  int * r = malloc (sizeof (int) * m * n);
  for (int i = 0; i < m * n; i++)
    scanf("%d ", r + i);

  return r;
}

void print_matrix (int * A, int m, int n)
{
  printf ("%d %d\n", m, n);

  for (int i = 0; i < m * n; i++)
    printf(
           (i + 1) % n ? "%d " : "%d\n"
           , A[i]);

}

int main (int argc, char ** argv)
{
  int *A = 0, *B = 0, *C;
  int m, n, o;

  while (scanf ("%d %d", &n, &o) != eof)
  {
    if (A == 0) 
    {
      A = read_matrix (n, o);
      m = n;
      n = o;
      continue;
    }
  
    B = read_matrix (n, o);
    C = mult (A, B, m, n, o);

    // print_matrix (B, n, o); 
    
    print_matrix (C, m, o);
    free (A);
    free (B);
    A = C;
    n = o;
  }
    

  return 0;
}
