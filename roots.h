#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX 100

double rtbis (double (*)(double), double, double, double, int*);
double rtnewt (void (*)(double, double*, double*),double, double, double, int*);
double rtiter (double (*)(double), double, double, int*);
double func (double);
double func1 (double);
void funcd (double, double*, double*);