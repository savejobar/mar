#include "roots.h" 

double rtbis (double (*func)(double), double x1, double x2, double xacc, int *err)
{
    double x, dx = 1;
    int i;
    for (i = 0; (i < MAX) && (dx > xacc); i++)
    { 
        if (i < MAX)
        {
            x = (x2 + x1)/2;
            if (func(x2)*func(x) < 0)
            {
                x1 = x;
            }
            else
            {
                x2 = x;
            }
            dx = fabs(x2-x1);
        } 
        else
        {
            printf ("i = %d\n",i);
            *err = 1;
            exit(*err);
        }     
    }
    printf ("i = %d\n",i);
    return x;
}

double rtnewt (void (*funcd)(double, double*, double*),double x1, double x2, double xacc, int *err)
{
    double x = (x2+x1) / 2.0, x_new, f, f1, dx = 1;
    int i;
    for (i = 0; (i < MAX) && (dx > xacc); i++)
    {
        if (f1 == 0) 
        {
            *err = 1;
            return x;
        }
        if (i < MAX)
        {
            funcd(x, &f, &f1);
            x_new = x-(f/f1);
            dx = fabs(x_new-x);
            x = x_new;
        }
        else 
        {
            printf ("i = %d\n" , i);
            *err = 1;
            return x_new;
        }
    }
    printf ("i = %d\n",i);
    return x_new;
}

double rtiter (double (*func)(double), double x1, double xacc, int *err)
{
    double x_new = 1, dx = 1;
    int i;
    for (i = 0; (i < MAX) && (dx > xacc); i++)
    {
        if (i < MAX)
        {
            x_new = func(x1);
            dx = fabs(x_new-x1);
            x1 = x_new;
        }
        else 
        {
            printf ("i = %d\n" , i);
            *err = 1;
            return x1;
        }
    }
    printf ("i = %d\n" , i);
    return x1;
}

double func (double x)
{
    return x*exp(x) - 1;
}

double func1 (double x)
{
    return 1/exp(x);
}

void funcd (double x, double *f, double *f1)
{
    double h = 1e-5;
    *f = func(x);
    *f1 = (func(x+h)-func(x-h))/(2*h);
}