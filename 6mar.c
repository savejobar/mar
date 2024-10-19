#include "funk_for_linal.c"

int main ()
{
    clock_t start = clock();
    srand(time(NULL));
    int n = 3;
    double **a1 = alloc2d(n,n);
    double *a = alloc1d(n);
    double *b = alloc1d(n);
    double *c = alloc1d(n);
    double *d = alloc1d(n);
    double *sol = alloc1d(n);
    random (a1,n,n,1,10);
    printf ("Matrix a1:\n");
    show2d (a1,n,n);
    random2 (d,n,1,10);
    printf ("d:\n");
    show1d (d,n);
    gauss (a1,d,sol,n);
    printf ("sol1:\n");
    show1d (sol,n);
    random2 (a,n,1,10), random2 (b,n,1,10), random2 (c,n,1,10), random2 (d,n,1,10);
    printf ("a:\n");
    show1d (a,n);
    printf ("b:\n");
    show1d (b,n);
    printf ("c:\n");
    show1d (c,n);
    printf ("d:\n");
    show1d (d,n);
    tridiag (a,b,c,d,sol,n);
    printf ("sol2:\n");
    show1d (sol,n);
    free2d(a1), free1d(a), free1d(b), free1d(c), free1d(d), free1d(sol);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time of work: %lf seconds\n", seconds);  
}