#ifndef MATRIXIO_H
#define MATRIXIO_H

int* read_matrix(int*,int*);
int** read_matrices(int**,int*);

int* fread_matrix(FILE*,int*,int*);
int** fread_matrices(FILE*,int**,int*);

void print_matrix(int*,int,int);
void print_paren(int*,int*,int);

void print_rand(int,int,int);

void print_extr(int*,int,int,int);

int matrix_equal (int*,int*,int,int);

#endif
