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
    printf ("trapz: %lf\n",trapz (function,a,b,n));
    printf ("simpson: %lf\n",simpson (function,a,b,n));
    printf ("trapz_adapt: %lf\n",trapz_adapt(function,a,b,eps));
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
    int n = 10000, precision = 2;
    double  x_new, q0 = trapz (function,a,b,n), q1 = q0, h = (b-a) / n;
    do
    {
        h /= precision;
        x_new = a + h;
        n *= precision;
        for (int i = 1; i <= n-1; ++i)
        {
            q1 += f(x_new);
            x_new += h; 
        }
        q1 *= h;
    }
    while (fabs(q1 - q0) > eps * fabs(q0));
    return q1;
}

double function (double x)
{
    return log(pow(x,14) + sqrt(x) + cbrt(x) + cos(2*x));
}
