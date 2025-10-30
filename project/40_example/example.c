#include <stdio.h>
#include <complex.h>

int main (void)
{
#ifdef __STDC_NO_COMPLEX
    printf ("Complex numbers are not supported\n");
    exit (1);
#else
    printf ("Complext numbers are supported\n");
    double complex cx = 1.0 + 3.0 * I;
    double complex cy = 1.0 - 4.0 * I;

    printf ("Working with complex numbers:\n");
    printf ("Starting values: cx = %.2f%+.2fi cy = %.2f%.2fi\n", creal (cx), cimag (cx), creal (cy), cimag (cy));

#endif
    return 0;
}