#ifndef LINAL
#define LINAL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double** alloc2d(int, int);
double* alloc1d(int);
void free2d (double**);
void free1d (double*);
double vabs (double*, int);
double scal_prod (double*, double*, int);
void fill (double**, int, int, double);
void matrix_prod (double**, double**, double**, int, int);
void show2d (double**, int, int);
void show1d (double*, int);
void random (double**, int, int, int, int);
void random2 (double *, int, int, int);
void gauss (double**, double*, double*, int);
void tridiag (double*, double*, double*, double*, double*, int);
void spline (double*, double*, int, double*);
void polation (double*, double*, int, double*, int);
int i, j, k;
#endif