#include<stdlib.h>
#include"extracted.h"

/* C <- A+B
 * A et B sont à coeffs nuls en dehors des blocs de tailles
 * mA*nA, mB*nB et on a ("left") mA>=mB, nA>=nB
 * */
void _addl (int * A, int * B, int * C,
               // Dim des sous-matrices
               int mA, int nA, int mB, int nB,
               // Nombre de colonnes des matrices totales
               int width_A, int width_B, int width_C)
{
  int i,j;
  // Matrice avec le moins de zones vides à gauche
  // Lignes de B
  for (int i = 0 ; i < mB ; i++)
  {
    // Colonnes de B non vides
    for (int j = 0 ; j < nB ; j++)
      C[j+i*width_C] = A[j+i*width_A] + B[j+i*width_B];
      
    // Colonnes de A "seules"
    for (int j = nB ; j < nA ; j++)
      C[j+i*width_C] = A[j+i*width_A];
  }
    
  // Lignes de A "seules" (et non vides)
  for (int i = mB ; i < mA ; i++)
    for (int j = 0 ; j < nA ; j++)
      C[j+i*width_C] = A[j+i*width_A];

  return;
}

void _addr (int * A, int * B, int * C,
                // Dim des sous-matrices
                int mA, int nA, int mB, int nB,
                // Nombre de colonnes des matrices totales
                int width_A, int width_B, int width_C)
{
  int i,j;
  // Matrice avec le moins de zones vides à droite
  for (int i = 0 ; i < mA ; i++)
  {
    for (int j = 0 ; j<nA ; j++)
      C[j+i*width_C] = A[j+i*width_A]+B[j+i*width_B];

    for (int j = nA ; j<nB ; j++)
      C[j+i*width_C] = B[j+i*width_B];
  }
    
  // Lignes de A "seules" (et non vides)
  for (int i = mA ; i < mB ; i++)
    for (int j = 0 ; j < nB ; j++)
      C[j+i*width_C] = B[j+i*width_B];

  return;
}

void _subl (int * A, int * B, int * C,
               // Dim des sous-matrices
               int mA, int nA, int mB, int nB,
               // Nombre de colonnes des matrices totales
               int width_A, int width_B, int width_C)
{
  int i,j;
  // Matrice avec le moins de zones vides à gauche
  // Lignes de B
  for (int i = 0 ; i < mB ; i++)
  {
    // Colonnes de B non vides
    for (int j = 0 ; j < nB ; j++)
      C[j+i*width_C] = A[j+i*width_A] - B[j+i*width_B];
      
    // Colonnes de A "seules"
    for (int j = nB ; j < nA ; j++)
      C[j+i*width_C] = A[j+i*width_A];
  }
    
  // Lignes de A "seules" (et non vides)
  for (int i = mB ; i < mA ; i++)
    for (int j = 0 ; j < nA ; j++)
      C[j+i*width_C] = A[j+i*width_A];

  return;
}

void _subr (int * A, int * B, int * C,
                // Dim des sous-matrices
                int mA, int nA, int mB, int nB,
                // Nombre de colonnes des matrices totales
                int width_A, int width_B, int width_C)
{
  int i,j;
  for (int i = 0 ; i < mA ; i++)
  {
    for (int j = 0 ; j<nA ; j++)
      C[j+i*width_C] = A[j+i*width_A]-B[j+i*width_B];

    for (int j = nA ; j<nB ; j++)
      C[j+i*width_C] = -B[j+i*width_B];
  }
    
  // Lignes de A "seules" (et non vides)
  for (int i = mA ; i < mB ; i++)
    for (int j = 0 ; j < nB ; j++)
      C[j+i*width_C] = -B[j+i*width_B];

  return;
}
#endif
