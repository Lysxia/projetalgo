#ifndef MATRIXIO_H
#define MATRIXIO_H

int * read_matrix(int*,int*);
void print_matrix(int*,int,int);
void print_paren(int*,int);

void print_extr(int*,int,int,int);
void _print_paren(int*,int,int);

bool matrix_equal (int*,int*,int,int);

#endif
