#ifndef STRASSEN_H
#define STRASSEN_H

#ifdef OSTRASSEN
#ifndef STOP
====== 'STOP' UNDEFINED
#endif
#define ENDREC(m,n,p) m<=STOP || n<=STOP || p<=STOP
#endif

int * strassen(int*,int*,int,int,int);
void _strassen(int*,int*,int*,int,int,int,int,int,int);

#endif
