#include "funk_for_linal.c"
#include "linal.h"

int main ()
{
    double one, two;
    FILE *f;
    int n = 0, kolvo_tochek = 20, sh = kolvo_tochek+1;
    if ( (f = fopen ("x,f(x).dat","r")) == NULL )
    {
        printf ("Error");
        exit (1);
    }
    while (fscanf(f,"%lf",&one) != EOF)
    {
        n++;
    }
    n /= 2;
    rewind (f);
    double *x = alloc1d(n);
    double *y = alloc1d(n);
    double *d2y = alloc1d(n);
    for (i = 0; i < n; i++)
    {
        fscanf(f,"%lf %lf", &one, &two);
        x[i] = one;
        y[i] = two;
    }
    spline (x,y,n,d2y);
    polation (x,y,n,d2y,sh);
    free1d(x), free1d(y), free1d(d2y);
    fclose(f);
}