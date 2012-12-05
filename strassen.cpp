#include<stdio.h>
#include<stdlib.h>
#include"strassen.h"

#define alloc(n) (sp += n * sizeof (int), sp - n * sizeof(int))

#define min(a,b) (a <= b ? a : b)
#define max(a,b) (a >= b ? a : b)

// Hell on earth
/* // M : résultat */
/* // l / c : lignes / colonnes (lettre correspondante) */
/* // i_l/i_c : indice de ligne/colonne */
/* #define __sub(A, M, l, c, i_l, i_c)  _sub (A##i_c##i_l, A##22, R, _m, _n, mA1, nA2, mA2, nA2, width_A, width_A, _n) */

int * mem = 0;
int * sp = 0;

int next_pow_2 (int n)
{
    int i=1;
    while (n>1)
    {
	i++;
	n>>=1;
    }
    return n<<i;
    // TODO : Demander directement la puissante de 2 supplementaire (assembleur)
}


int * read_matrix (int m, int n)
{
  /* int _m, _n; */
  /* _m = next_pow_2 (m); */
  /* _n = next_pow_2 (n); */

  int * r = alloc (m * n);

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


int * strassen (int * A, int * B, int m, int n, int o)
{
  int *C = alloc (m * o);
}


// WANRING : la matrice indiquée par "big_left" (càd gauche si true) doit 
// TOUJOURS être celle qui a le plus de colonnes non vides
// Dans l'algorithme, on peut toujours la prendre ayant également
// le plus de lignes non vides
// WANRING : il faudra parfois inverser la matrice résultat
template<bool sub, bool big_left>
void _add (int * A, int * B, int * C,
           // Dimensions abstraites
           int m, int n,
           // Dim des sous-matrices non nulles
           int mA, int nA, int mB, int nB,
           // Nombre de colonnes des matrices totales
           int width_A, int width_B, int width_C)
{
  if (big_left)
  {
    // Matrice avec le moins de zones vides à gauche
    // Lignes de B non vides
    for (int i = 0; i < mB; i++)
    {
      // Colonnes de B non vides
      for (int j = 0; j < nB; j++)
	if (sub)
	  C[j + i * width_C] = A[j + i * width_A] - B[j + i * width_B];
	else
	  C[j + i * width_C] = A[j + i * width_A] + B[j + i * width_B];
      
      // Colonnes de A "seules"
      for (int j = nB; j < nA; j++)
	C[j + i * width_C] = A[j + i * width_A];
    }
    
    // Lignes de A "seules" (et non vides)
    for (int i = mB; i < mA; i++)
      for (int j = 0; j < nA; j++)
	C[j + i * width_C] = A[j + i * width_A];

  } 
  else
  {
    // Matrice avec le moins de zones vides à droite
    // TODO 
  }
  
}


// WANRING : la matrice A doit TOUJOURS être celle qui a le plus de
// colonnes non vides
// Dans l'algorithme, on peut toujours la prendre ayant également
// le plus de lignes non vides
// void _add (int * A, int * B, int * C,
//            // Dimensions abstraites
//            int m, int n,
//            // Dim des sous-matrices non nulles
//            int mA, int nA, int mB, int nB,
//            // Nombre de colonnes des matrices totales
//            int width_A, int width_B, int width_C)
// {
//   // Lignes de B non vides
//   for (int i = 0; i < mB; i++)
//   {
//     // Colonnes de B non vides
//     for (int j = 0; j < nB; j++)
//       C[j + i * width_C] = A[j + i * width_A] + B[j + i * width_B];
    
//     // Colonnes de A "seules"
//     for (int j = nB; j < nA; j++)
//       C[j + i * width_C] = A[j + i * width_A];
//   }

//   // Lignes de A "seules" (et non vides)
//   for (int i = mB; i < mA; i++)
//     for (int j = 0; j < nA; j++)
//       C[j + i * width_C] = A[j + i * width_A];

// }


// WANRING : la matrice A doit TOUJOURS être celle qui a le plus de
// colonnes non vides
// Dans l'algorithme, on peut toujours la prendre ayant également
// le plus de lignes non vides
// WANRING : il faudra parfois inverser la matrice résultat
// void _sub (int * A, int * B, int * C,
//            // Dimensions abstraites
//            int m, int n,
//            // Dim des sous-matrices non nulles
//            int mA, int nA, int mB, int nB,
//            // Nombre de colonnes des matrices totales
//            int width_A, int width_B, int width_C)
// {
//   // Lignes de B non vides
//   for (int i = 0; i < mB; i++)
//   {
//     // Colonnes de B non vides
//     for (int j = 0; j < nB; j++)
//       C[j + i * width_C] = A[j + i * width_A] - B[j + i * width_B];
    
//     // Colonnes de A "seules"
//     for (int j = nB; j < nA; j++)
//       C[j + i * width_C] = A[j + i * width_A];
//   }

//   // Lignes de A "seules" (et non vides)
//   for (int i = mB; i < mA; i++)
//     for (int j = 0; j < nA; j++)
//       C[j + i * width_C] = A[j + i * width_A];

// }


void _strassen (int * A, int * B, int * C, 
                // Dimensions abstraites
                int m, int n, int o, 
                // Dim des sous-matrices non nulles
                int mA, int nA, int nB, int oB, 
                // Nombre de colonnes des matrices totales
                int width_A, int width_B, int width_C)
{
  if (mA <= 0 || nA <= 0 || nB <= 0 || oB <= 0)
    return;

  // A n'est plus qu'une matrice ligne... On multiplie à la main
  if (m == 1)
  {
    for (int k = 0; k < oB; k++)
    {
      // Initialisation
      C[k] = 0;
      
      for (int j = 0; j < (nA < nB) ? nA : nB; j++)
        // Note : i est implicite, il vaut 0 (une seule ligne)
        C[k] += A[j] * B[k + j * width_B];
    }

    return;
  }

  // Idem, cette fois B n'est plus qu'une matrice colonne
  if (o == 1)
  {
    for (int i = 0; i < nA; i++)
    {
      C[i * width_C] = 0;
      
      for (int j = 0; j < (nA < nB) ? nA : nB; j++)
        // Note : k est implicite (k = 0)
        C[i * width_C] += A[j + i * width_A] * B[j * width_B];
    }

    return;
  }

  // Dimension commune = 1
  if (n == 1)
  {
    for (int i = 0; i < mA; i++)
      for (int k = 0; k < oB; k++)
        C[i * width_C + k] = A[i * width_A] * B[k];

    return;
  }

  // TODO : allouer les X dans des P
  // -> on mettra X7 dans P11 et X6 dans P22

  int * M, *N;
  // Petites dimensions
  int _m = (m+1) / 2;
  int _n = (n+1) / 2;
  int _o = (o+1) / 2;

  M = alloc ( _m * _n);
  N = alloc ( _n * _o);


  int * X4 = C + width_C * _m;      // X4 = P21
  int * X5 = C + _o;                // X5 = P12
  int * X6 = C + _o + width_C * _m; // X6 = P22
  int * X7 = C;                     // X7 = P11
  
  // Sous-matrices de A
  int * A11 = A;     
  int * A12 = A + _n;
  int * A21 = A + _m * width_A;
  int * A22 = A + _m * width_A + _n;
  // Indices de non-nullité des sous-matrices de A
  int mA1 = min (mA, _m);
  int mA2 = mA - _m;
  int nA1 = min (nA, _n);
  int nA2 = nA - _n;


  // Sous-matrices de B
  int * B11 = B;     
  int * B12 = B + _o;
  int * B21 = B + _n * width_B;
  int * B22 = B + _n * width_B + _o;
  // Indices de non-nullité des sous-matrices de B
  int nB1 = min (nB, _n);
  int nB2 = nB - _n;
  int oB1 = min (oB, _o);
  int oB2 = oB - _o;

  

  int * X = alloc (_m * _o);
  
  // Calcul de X7
    // M12 - M22
  _add<true, true> (A12, A22, M, _m, _n, mA1, nA2, mA2, nA2, width_A, width_A, _n);
    // N21 + N22
  _add<false, true> (B21, B22, N, _m, _n, mA2, nA1, mA2, nA2, width_A, width_A, _n);

  _strassen (M, N, X7, _m, _n, _o, 
             mA1, // Forcément plus grand que mA2
             nA2, mA2, 
             nA1, // Forcément plus grand que nA2
             _n, _o, width_C);


  // Calcul de X6
    // M11 - M21 (à inverser)
  _add<true, true> (A21, A22, M, _m, _n, mA1, nA2, mA2, nA2, width_A, width_A, _n);
    // N21 + N22
  _add<false, true> (B21, B22, N, _m, _n, mA2, nA1, mA2, nA2, width_A, width_A, _n);
  
}

int main ()
{
  // if (NULL == (mem = malloc (3000000000)))
  if (0 == (mem = (int*) malloc (3000000000u)))
  {
    printf("Major failure ! Memory not allocated. Bye\n");
    return 1;
  }

  sp = mem;

  // No need to free : the OS will clean everything...

  return 0;
}
