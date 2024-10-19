#include "roots.c"
#include "roots.h" 

int main ()
{
    double x1 = 0, x2 = 2, xacc = 1e-8;
    int err = 0;
    printf ("Method 1:\n");
    printf ("x = %lf\n\n",rtbis(func,x1,x2,xacc,&err));
    printf ("Method 2:\n");
    printf ("x = %lf\n\n",rtnewt(funcd,x1,x2,xacc,&err));
    printf ("Method 3:\n");
    printf ("x = %lf\n",rtiter(func1,x1,xacc,&err));
    return err;
}