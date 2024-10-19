#include "funk_for_linal.c"

int main ()
{
    clock_t start = clock();
    int str = 2, stl = 2, n = 2;
    double scal_1[] = {2,2,2}, scal_2[] = {-2,4,0};
    double x = 1.0;
    double **a = alloc2d(str,stl);
    double **b = alloc2d(str,stl);
    double **c = alloc2d(str,stl);
    printf ("vabs = %lf\n",vabs (scal_1,2));
    printf ("scal_prod = %lf\n",scal_prod(scal_1,scal_2,n));
    printf ("\n");
    fill (a,str,stl,x);
    fill (b,str,stl,x);
    show2d (a,str,stl);
    printf ("\n");
    show2d (b,str,stl);
    matrix_prod (a,b,c,str,stl);
    printf ("\n");
    show2d (c,str,stl);
    free2d(a);
    free2d(b);
    free2d(c);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time of work: %lf seconds\n", seconds);  
}
