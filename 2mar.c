#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EULER 0.57721566490153286061
#define MAXIT 100
#define EPS 1.e-6

double Ei (double);

int main() 
{   
    clock_t start = clock();
    double x,xmin = 0.0001,xmax = 700,sh = 2; double tmp; 
    int ch, flag = 0;
    FILE *fp;
    printf ("Enter Xmin, Xmax and step: \n");
    //scanf ("%lf%lf%lf",&xmin,&xmax,&sh);
    if ( (fp = fopen ("ei.dat","w")) == NULL )
    {
        printf ("Error");
        exit (1);
    }
    for (x = xmin; x < fabs(log(EPS)); x *= sh)
    {
        if (Ei(x) && flag == 0)
        {
           fprintf (fp,"Small values:\n");
           fprintf (fp, "x = %.2e\tS = %.2e\n",x,Ei(x));
           flag = 1;
        }
        else
        {
           fprintf (fp, "x = %.2e\tS = %.2e\n",x,Ei(x));
        }
    }
    tmp = x;
    flag = 0;
    for (x = tmp; x < xmax; x *= sh)
    {
        if (Ei(x) && flag == 0)
        {
           fprintf (fp,"Huge values:\n");
           fprintf (fp, "x = %.2e\tS = %.2e\n",x,Ei(x));
           flag = 1;
        }
        else
        {
           fprintf (fp, "x = %.2e\tS = %.2e\n",x,Ei(x));
        }
    }
    fclose(fp);
    if ( (fp = fopen ("ei.dat","r")) == NULL )
    {
        printf ("Error");
        exit (1);
    }
    while (!(feof(fp)))
    {
        ch = getc (fp);
        putchar(ch);
    }
    fclose(fp);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time of work: %f seconds\n", seconds);
}
 
double Ei (double x)
{
    double t=1; int n;
    if (x < fabs(log(EPS)))
    {
        double S = EULER + log(x);
        for (n = 1; (t > EPS*S) && (n < MAXIT) ; n++)
        {
            t *= x*n/(n+1)/(n+1);
            S += t;
        }
        return S;
    }
    else if (x > fabs(log(EPS)))
    {
        double S = 1;
        for (n = 0; (t > EPS) && (n < MAXIT); n++)
        { 
            t *= (n+1)/x;
            S += t;
        }
        return S*exp(x)/x;
    } 
    else
    {
        return 0;
    }
}
