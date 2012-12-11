#include<stdlib.h>
#include<stdio.h>
#include"strassen.h"
#include"matrixio.h"

#define min(a,b) (a <= b ? a : b)
#define max(a,b) (a >= b ? a : b)


/* Représentation brute d'une matrice m*n :
 *   - Pointeur sur la case (0,0) : M
 *   - Largeur : n
 *   - Accès à la case (i,j) : M[i*n+j]
 *
 * Représentation d'une sous-matrice m'*n' de M :
 *   - Pointeur sur la case (0,0) : M'
 *   - Largeur : n
 *   - Accès à la case (i,j) : M'[i'*n+j']
 *
 * Les fonctions _add et _strassen utilisent
 * la représentation en sous-matrice.
 */


int * mem = 0;
int * sp = 0;

/* Cette fonction recoit deux matrices dans la représentation brute */
int * strassen (int * A, int * B, int m, int n, int o)
{
  /* Pour économiser des appels à malloc on alloue la mémoire
   * nécessaire d'avance pour la fonction strassen */
  if (0 == (mem = (int*) malloc (1000000000*sizeof(int))))
  {
    printf("Major failure ! Memory not allocated. Bye.\n");
    return 0;
  }

  sp = mem;

  int *C;

  if (0 == (C = (int*) malloc (m*o*sizeof(int))))
      return 0;

  _strassen(A, B, C, m, n, o, n, o, o);

  return C;
}


// Représentation en sous-matrices
void _strassen (int * A, int * B, int * C, 
                // Dim des matrices
                int m, int n, int o, 
                // Nombre de colonnes des matrices totales
                int width_A, int width_B, int width_C)
{
  if (m <= 0 || n <= 0 || o <= 0)
    return;

  // A n'est plus qu'une matrice ligne... On multiplie à la main
  if (m == 1)
  {
    for (int k = 0; k < o; k++)
    {
      // Initialisation
      C[k] = 0;
      
      for (int j = 0 ; j < n ; j++)
        // Note : i est implicite, il vaut 0 (une seule ligne)
        C[k] += A[j] * B[k + j * width_B];
    }

    //print_extr(C,m,o,width_C);
    return;
  }

  // Idem, cette fois B n'est plus qu'une matrice colonne
  if (o == 1)
  {
    for (int i = 0; i < m; i++)
    {
      C[i * width_C] = 0;
      
      for (int j = 0; j < n; j++)
        // Note : k est implicite (k = 0)
        C[i * width_C] += A[j + i * width_A] * B[j * width_B];
    }

    //print_extr(C,m,o,width_C);
    return;
  }

  // Dimension commune = 1
  if (n == 1)
  {
    for (int i = 0; i < m; i++)
      for (int k = 0; k < o; k++)
        C[i * width_C + k] = A[i * width_A] * B[k];

    //print_extr(C,m,o,width_C);
    return;
  }

  // Petites dimensions
  int m1 = (m+1)/2;
  int m2 = m-m1; // always *2 <= *1
  int n1 = (n+1)/2;
  int n2 = n-n1;
  int o1 = (o+1)/2;
  int o2 = o-o1;

  // Allocation de la mémoire
  int * M = sp;
  int * N = sp+m1*n1;
  int * X = sp+m1*n1+n1*o1;

  sp += m1*n1+n1*o1+m1*o1;


  int * X4 = C + width_C * m1;      // X4 = P21
  int * X5 = C + o1;                // X5 = P12
  int * X6 = C + o1 + width_C * m1; // X6 = P22
  int * X7 = C;                     // X7 = P11
  
  // Sous-matrices de A
  int * A11 = A;     
  int * A12 = A + n1;
  int * A21 = A + m1 * width_A;
  int * A22 = A + m1 * width_A + n1;

  // Sous-matrices de B
  int * B11 = B;     
  int * B12 = B + o1;
  int * B21 = B + n1 * width_B;
  int * B22 = B + n1 * width_B + o1;


  // TODO : script-générer les calculs suivants
  
  // Calcul de X7
    // M <- A12 - A22
  _add<true, true> (A12, A22, M, m1, n2, m2, n2, width_A, width_A, n1);
    // N <- B21 + B22
  _add<false, true> (B21, B22, N, n2, o1, n2, o2, width_B, width_B, o1);

  // X7 <- M * N
  _strassen (M, N, X7,
             m1, n2, o1,
             n1, o1, width_C);
  


  // Calcul de X6
    // M <- A21 - A11
  _add<true, false> (A21, A11, M, m2, n1, m2, n1, width_A, width_A, n1);
    // N <- B11 + B12
  _add<false, true> (B11, B12, N, n1, o2, n1, o2, width_B, width_B, o1);

  // X6 <- M * N
  _strassen (M, N, X6,
             m2, n1, o2,
             n1, o1, width_C);
  

  // Calcul de X5
    // M <- A11 + A12
  _add<false, true> (A11, A12, M, m1, n2, m1, n2, width_A, width_A, n1);

  // X5 <- M * B22
  _strassen (M, B22, X5,
             m1, n2, o2,
             n1, width_B, width_C);


  // Calcul de X4
    // N <- B21 - B11
  _add<true, false> (B21, B11, N, n2, o1, n2, o1, width_B, width_B, o1);

  // X4 <- A22 * N
  _strassen (A22, N, X4,
             m2, n2, o1,
             width_A, o1, width_C);

  // X7 (P11) <- X7 + X4
  _add<false, true> (X7, X4, X7,
	  // Note : on passe la taille de X4 à chaque fois
	  //        pour éviter les parcours inutiles
                    m2, o1, m2, o1,
                    width_C, width_C, width_C);

  // X7 <- X7 - X5
  _add<true, true> (X7, X5, X7, m1, o2, m1, o2, width_C, width_C, width_C);


  // Calcul de X3
    // N <- B12-B22
  _add<true, true> (B12, B22, N, n1, o2, n2, o2, width_B, width_B, o1);

  // X (X3) <- A11 * N
  _strassen (A11, N, X,
	     m1, n1, o2,
	     width_A, o1, o1);

  // X5 (P12) <- X5 + X3
  _add<false, true> (X, X5, X5, m1, o2, m1, o2, o1, width_C, width_C);

  // X6 (P22) <- X6 + X3
  _add<false, true> (X, X6, X6, m2, o2, m2, o2, o1, width_C, width_C);


  // Calcul de X2
    // M <- A21 + A22
  _add<false, true> (A21, A22, M, m2, n1, m2, n2, width_A, width_A, n1);

  // X (X2) <- M * B11
  _strassen (M, B11, X,
	     m2, n1, o1,
	     n1, width_B, o1);

  // X4 (P21) <- X4 + X2
  _add<false, true> (X4, X, X4, m2, o1, m2, o1, width_C, o1, width_C);

  // X6 (P22) <- X6 - X2
  _add<true, true> (X6, X, X6, m2, o2, m2, o2, width_C, o1, width_C);


  // Calcul de X1
    // M <- A11 + A22
  _add<false, true> (A11, A22, M, m1, n1, m2, n2, width_A, width_A, n1);
    // N <- B11 + B22
  _add<false, true> (B11, B22, N, n1, o1, n2, o2, width_B, width_B, o1);

  // X (X1) <- M * N
  _strassen (M, N, X,
	     m1, n1, o1,
	     n1, o1, o1);

  // X7 (P11) <- X7 + X1
  _add<false, true> (X7, X, X7, m1, o1, m1, o1, width_C, o1, width_C);

  // X6 (P22) <- X6 + X1
  _add<false, true> (X6, X, X6, m2, o2, m2, o2, width_C, o1, width_C);

  sp -= m1*n1+n1*o1+m1*o1;

  //print_extr(C,m,o,width_C);
  return;

}

