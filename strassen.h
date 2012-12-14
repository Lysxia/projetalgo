#ifndef STRASSEN_H
#define STRASSEN_H
#include"matrixio.h"
#include"const.h" 

#define ENDREC(m,n,p) m<=STOP || n<=STOP || p<=STOP

int * strassen(int*,int*,int,int,int);
void _strassen(int*,int*,int*,int,int,int,int,int,int);

// WANRING : la matrice indiquée par "big_left" (càd gauche si true) doit 
// TOUJOURS être celle qui a le plus de colonnes non vides
// Dans l'algorithme, on peut toujours la prendre ayant également
// le plus de lignes non vides
// WANRING : il faudra parfois inverser la matrice résultat
// TODO : faire une macro pour ça :D
template<bool sub, bool big_left>
inline
void _add (int * A, int * B, int * C,
           // Dim des sous-matrices
           int mA, int nA, int mB, int nB,
           // Nombre de colonnes des matrices totales
           int width_A, int width_B, int width_C)
{
  if (big_left)
  {
    // Matrice avec le moins de zones vides à gauche
    // Lignes de B
    for (int i = 0 ; i < mB ; i++)
    {
      // Colonnes de B non vides
      for (int j = 0 ; j < nB ; j++)
	if (sub)
	  C[j+i*width_C] = A[j+i*width_A] - B[j+i*width_B];
	else
	  C[j+i*width_C] = A[j+i*width_A] + B[j+i*width_B];
      
      // Colonnes de A "seules"
      for (int j = nB ; j < nA ; j++)
	C[j+i*width_C] = A[j+i*width_A];
    }
    
    // Lignes de A "seules" (et non vides)
    for (int i = mB ; i < mA ; i++)
      for (int j = 0 ; j < nA ; j++)
	C[j+i*width_C] = A[j+i*width_A];
  }
  else
  {
    // Matrice avec le moins de zones vides à droite
    for (int i = 0 ; i < mA ; i++)
    {
	for (int j = 0 ; j<nA ; j++)
	    if (sub)
		C[j+i*width_C] = A[j+i*width_A]-B[j+i*width_B];
	    else
		C[j+i*width_C] = A[j+i*width_A]+B[j+i*width_B];

	for (int j = nA ; j<nB ; j++)
	    C[j+i*width_C] = (sub) ? -B[j+i*width_B] : B[j+i*width_B];
    }
    
    // Lignes de A "seules" (et non vides)
    for (int i = mA ; i < mB ; i++)
      for (int j = 0 ; j < nB ; j++)
	C[j+i*width_C] = (sub) ? -B[j+i*width_B] : B[j+i*width_B];
  }

  //print_extr(C,(big_left)?mA:mB,(big_left)?nA:nB,width_C);
  return;
}

// Equivalent de += ou -=
template<bool sub>
inline
void _add_in (int *A, int *B, int m, int n, int width_A, int width_B)
{
    for (int i=0 ; i<m ; i++)
        for (int j=0 ; j<n ; j++)
	{
	    if (sub)
	        A[j+i*width_A]-=B[j+i*width_B];
	    else
		A[j+i*width_A]+=B[j+i*width_B];
	}
    return;
}

#endif
