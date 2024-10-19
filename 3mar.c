#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() 
{   
    clock_t start = clock();
    int i=0; double sum=0,sr=0,j,diff=0,sigm=0,S=0,k=0,x;
    start = clock();
    FILE *f;
    if ( (f = fopen ("chisla.dat","r")) == NULL )
    {
        printf ("Error");
        exit (1);
    }
    if (!(feof(f)))
    {
        while (fscanf(f,"%lf",&x) != EOF)
        {
            i++;
            sum += x;
        }
        sr = sum / i;
        sum = 0;
        rewind (f);
        while (fscanf(f,"%lf",&x) != EOF)
        {
            diff = pow((x - sr),2);
            sum += diff;
        }
        sigm = sum / (i-1);
        sum = 0;
        rewind (f);
        while (fscanf(f,"%lf",&x) != EOF)
        {
            diff = pow(((x - sr) )/ sqrt(sigm),3);
            sum += diff;
        }
        S = sum / i;
        sum = 0;
        rewind (f);
        while (fscanf(f,"%lf",&x) != EOF)
        {
            diff = pow(((x - sr) ) / sqrt(sigm),4);
            sum += diff;
        }
        k = (sum / i) - 3;
    }
    printf ("Middle value is:\t%.2e\n",sr);
    printf ("Variance value is:\t%.2e\n",sigm);
    printf ("Skewness is:\t%.2e\n",S);
    printf ("Kurtosis is:\t%.2e\n",k);
    fclose(f);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time of work: %f seconds\n", seconds);  
}