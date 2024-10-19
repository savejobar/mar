#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef double (*finteg) (double);
double trapz (finteg, double, double, int);
double simpson (finteg, double, double, int);
double trapz_adapt (finteg, double, double, double);
double function (double);

int n = 10000;

int main() 
{   
    clock_t start = clock();
    double a = 3, b = 10.0, eps = 1e-6;
    printf ("trapz: %.5lf\n",trapz (function,a,b,n));
    printf ("simpson: %.5lf\n",simpson (function,a,b,n));
    printf ("trapz_adapt: %.5lf\n",trapz_adapt(function,a,b,eps));
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time of work: %f seconds\n", seconds);
}

double trapz (finteg f, double a, double b, int n)
{   double h = (b-a) / n;
    double x0 = a, x1 = a + h, xn = x1 + n*h;
    double sum=0.5*f(xn) +  0.5*f(x0);
    for (int i = 1; i <= n-1; i++)
    {
        sum += f(x1);
        x1 += h;
    }
    return sum * h;
}

double simpson (finteg f, double a, double b, int n)
{
    double h = (b-a) / n;
    double x0 = a, x1 = a + h, x2 = x1+h, xn = x1 + n*h, xn_minus_1 = xn - h, xn_minus_2 = xn -2*h , x3 = x2 + h;
    double sum = 3*(f(x0) + f(xn))/8 + 7*(f(x1) + f(xn_minus_1))/6 + 23*(f(x2) + f(xn_minus_2))/24;
    for (int i = 3; i <= n-3; i++)
    {
        sum += f(x3);
        x3 += h;
    }
    return sum * h;
}

 double trapz_adapt (finteg f, double a, double b, double eps)
{
    double h = (b-a) / n;
    double x0_new = a/2, x1_new = (a + h) / 2, xn_new = (x1_new + n*h) / 2;
    double sum=0.5*f(xn_new) + 0.5*f(x0_new),rez;
    do
    {
       sum += f(x1_new);
       x1_new += h / 2;
       rez = sum*h*0.5 + trapz (function,a,b,n);
    }
    while (fabs(trapz(function,a,b,n) - rez) < (eps * trapz(function,a,b,n)));
    // printf ("\n%.5lf\n%.5lf\n%.5lf\n",sum*h*0.5,trapz(function,a,b,n),rez);
    return rez;
}

double function (double x)
{
    return log(pow(x,10) + sqrt(x) + cbrt(x) + sin(x));
}
