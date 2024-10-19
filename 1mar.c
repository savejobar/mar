#include <stdio.h> 
#include <math.h>
#include <complex.h>

void eq2 (double, double,
double, double complex*, double complex *);

void eq2_correct (double, double,
double, double complex*, double complex *);

void eq3 (double, double, double,
double complex*, double complex*,
double complex*);


int main() 
{   
    double a=1.0,b=2.0,c=5.0;
    double complex r1,r2,r3;
    if ((a*c > b*b*0.01) && sqrt(b*b-4*a*c) >= 0)
    {
    eq2 (a,b,c,&r1,&r2);
    printf ("\neq2 is working:\nx1 = %.2e\nx2 = %.2e\n",creal(r1),creal(r2));
    }
    else
    {
    eq2_correct (a,b,c,&r1,&r2);
    printf ("\neq2_correct is working:\nx1 = %.2e + %.2ei\n",creal(r1),cimag(r1));
    printf ("x2 = %.2e + %.2ei\n",creal(r2),cimag(r2));
    }

    a = 1.0; b = 2.0; c = 1.0;
    eq3 (a,b,c,&r1,&r2,&r3);
    printf ("\n1 Complex and 2 real roots:\nx1 = %.2e + %.2ei\n",creal(r1),cimag(r1));
    printf ("x2 = %.2e + %.2ei\n",creal(r2),cimag(r2));
    printf ("x3 = %.2e + %.2ei\n",creal(r3),cimag(r3));

    a = 10.0; b = 20.0; c = 1.0;
    eq3 (a,b,c,&r1,&r2,&r3);
    printf ("\nReal roots:\nx1 = %.2e + %.2ei\n",creal(r1),cimag(r1));
    printf ("x2 = %.2e + %.2ei\n",creal(r2),cimag(r2));
    printf ("x3 = %.2e + %.2ei\n",creal(r3),cimag(r3));
}

void eq2 (double a, double b ,
double c, double complex *x1, double complex *x2)
{ 
    *x1 = (-b + sqrt(b*b-4*a*c))/(2.0*a);
    *x2 = (-b - sqrt(b*b-4*a*c))/(2.0*a);
}
void eq2_correct (double a, double b,
double c, double complex *x1, double complex *x2)
{
    double D = sqrt(b*b-4.0*a*c);
    if (D >= 0)
    {
        double q = (-0.5)*(b+copysign(1,b)*sqrt(b*b-4*a*c));
        *x1 = q/a;
        *x2 = c/q;
    } 
    else
    {
        double complex q = (-0.5)*(b+copysign(1,b)*I*sqrt(fabs(b*b-4*a*c)));
        *x1 = q/a;
        *x2 = c/q;
    } 
}

void eq3 (double a, double b, double c,
double complex *x1, double complex *x2,
double complex *x3)
{   
    double Q = (a*a-3.0*b)/9.0, R = (2*a*a*a-9*a*b+27.0*c)/54.0;
    if (R*R < Q*Q*Q)
    {
        double t = acos(R/(sqrt(Q*Q*Q)));
        *x1 = (-2)*sqrt(Q)*cos(t/3)-(a/3);
        *x2 = (-2)*sqrt(Q)*cos((t+2*M_PI)/3)-(a/3);
        *x3 = (-2)*sqrt(Q)*cos((t-2*M_PI)/3)-(a/3);
    }
    else
    {
        double A = -copysign(1.0,R)*cbrt((fabs(R) + sqrt(R*R-Q*Q*Q)));
        double B;
        if (A)
        {
            B = Q / A;
        }
        else
        {
            B = 0.0;
        }
        *x1 = A + B - a/3;
        *x2 = -0.5*(A+B) - a/3 + sqrt(3)*(A-B)*0.5*I;
        *x3 = -0.5*(A+B) - a/3 - sqrt(3)*(A-B)*0.5*I;
    }
}  