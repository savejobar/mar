#include "linal.h"

double* alloc1d(int n)
{
    double *a;
    a = (double*)malloc(n*sizeof(double));
    return a;
}

double** alloc2d (int n1 , int n2)
{
    double **a;
    a = (double**)malloc(n1*sizeof(double*) + n1*n2*sizeof(double));
    for (i = 0; i < n1; i++)
    {
        a[i] = (double*)(a+n1) + i*n2;
    }
    return a;
}

void free1d (double *a)
{
    free(a);
}

void free2d (double **a)
{
    free(a);
}

double vabs (double *a, int n)
{
    double sum;
    for (i = 0; i < n; i++)
    {
      sum += pow(*(a+i),2);      
    }
    return (sqrt(sum));
}

double scal_prod (double *a, double *b, int n) 
{
    double sum;
    for (i = 0; i < n; i++)
    {
      sum += (*(a+i)) * (*(b+i));      
    }
    return sum;
}

void fill (double **a, int n1, int n2, double x)
{
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            a[i][j] = x;
        }
    }
}
void matrix_prod (double **a, double **b, double **c, int n1, int n2)
{
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            c[i][j] = 0;
        }
    }
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            for (int k = 0; k < n2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    } 
}

void show1d (double *a, int n)
{
    for (i = 0; i < n; i++)
    {
        printf (" %lf",a[i]);
        printf ("\n"); 
    }
}

void show2d (double **a, int n1, int n2)
{
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            printf (" %2.1lf",a[i][j]);
        } 
        printf ("\n"); 
    }
}

void random (double **a, int n1, int n2, int min, int max)
{
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            a[i][j] = rand () % (max-min+1) + min;
        }
    }
}

void random2 (double *a, int n, int min, int max)
{
    for (i = 0; i < n; i++)
    {
            *(a+i) = rand () % (max-min+1) + min;
    }
}

void gauss (double **a, double *d, double *sol, int n)
{
    for (k = 0; k < n - 1; k++) 
    {
        double tmp = a[k][k];
        for (i = k + 1; i < n; i++) 
        {
            double lik = a[i][k] / tmp;
            for (j = k; j < n; j++)
            {
                a[i][j] -= lik * a[k][j];
            }
            d[i] -= lik * d[k];
        }
    }
    for (k = n - 1; k >= 0; k--) 
    {
        sol[k] = d[k];
        for (i = k + 1; i < n; i++)
        {
            sol[k] -= a[k][i] * sol[i];
        }
        sol[k] /= a[k][k];
    }
}

void tridiag (double *a, double *b, double *c, double *d, double *sol, int n)
{
    a[0] = 0;
    c[n-1] = 0;
    double c_new[n], d_new[n];
    if (fabs(b[0]) > 1e-9)
    {
    c_new[0] = c[0]/b[0];
    d_new[0] = d[0]/b[0];
    }
    else
    {
    c_new[0] = 0;
    d_new[0] = 0;
    }
    for (i = 1; i <= n-2; i++)
    {
        c_new[i] = c[i]/(b[i]-a[i]*c_new[i-1]);
    }
    for (i = 1; i <= n-1; i++)
    {
        d_new[i] = (d[i]-a[i]*d_new[i-1])/(b[i]-a[i]*c_new[i-1]);
    }
    sol[n-1] = d_new[n-1];
    for (i = n-2; i >= 0; i--)
    {
        sol[i] = d_new[i] - c_new[i]*sol[i+1];
    }
}

void spline (double *x, double *y, int n, double *d2y)
{
    double a[n], b[n], c[n], d[n], c_new[n], d_new[n], h, h1;
    for (i = 1; i <= n-1; i++)
    {
        h = x[i] - x[i-1];
        h1 = x[i+1] - x[i];
        a[i] = h / 6;
        b[i] = (x[i+1] - x[i-1])/3;
        c[i] = h1 / 6;
        d[i] = ((y[i+1] - y[i])/h1) - ((y[i] - y[i-1])/h);
    }
    a[0] = 0;
    c[n-1] = 0;
    if (fabs(b[0]) > 1e-9)
    {
    c_new[0] = c[0]/b[0];
    d_new[0] = d[0]/b[0];
    }
    else
    {
    c_new[0] = 0;
    d_new[0] = 0;
    }
    for (i = 1; i <= n-2; i++)
    {
        if (fabs(b[i]-a[i]*c_new[i-1]) > 1e-9)
        {
            c_new[i] = c[i]/(b[i]-a[i]*c_new[i-1]);
        }
        else
        {
            c_new[i] = 0;
        }
    }
    for (i = 1; i <= n-1; i++)
    {
        if (fabs(b[i]-a[i]*c_new[i-1]) > 1e-9)
        {
            d_new[i] = (d[i]-a[i]*d_new[i-1])/(b[i]-a[i]*c_new[i-1]);
        }
        else
        {
            d_new[i] = 0;
        }
    }
    d2y[n-1] = d_new[n-1];
    for (i = n-2; i >= 0; --i)
    {
        d2y[i] = d_new[i] - c_new[i]*d2y[i+1];
    } 
    d2y[0] = 0, d2y[n-1] = 0;
}

void polation (double *x, double *y, int n, double *d2y, int sh)
{
    double *spline = (double*)malloc(n*sh*sizeof(double));
    double point, step, h, A, B, C, D;
    for (i = 0; i < n; i++)
    {
        spline [sh*i] = y[i];
    }
    for (i = 0, j = 0; i < n - 1; i++) 
    {
        h = x[i+1] - x[i]; 
        step = h / sh;
        point = x[i]; 
        for (k = 0; k < sh; k++) 
        {
            point += step; 
            double A = (x[i+1]-point)/h;
            double B = 1 - A;
            double C = ((A*A*A-A)*(h*h))/6;
            double D = ((B*B*B-B)*(h*h))/6;
            spline[j+1] = A*y[i]+B*y[i+1]+C*d2y[i]+D*d2y[i+1];
            j++;
        }
    }
    point = x[0];
    for (i = 0; i < sh*(n-1)+1; i++)
    {
        step = (x[i/sh+1] - x[i/sh]) / sh;
        printf ("f(%2lf) = %5lf\n",point,spline[i]);
        point += step;
    }  
    free (spline);
}