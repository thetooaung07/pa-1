#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "float.h"


int main(void) {
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;

    if (a + b == c) {
        printf("Of course this holds, bruh!\n");
    } else {
        printf("No way! Wut? ¯\\_(ツ)_/¯\n");
    }

    printf("Explonation here.:\n");
    printf("a = %.20f\nb = %.20F\nc = %.20F\na+b = %.20F\n", a, b, c, a + b);


    if (fabs(a + b - c) < DBL_EPSILON) {
        printf("Same in the tolerance\n");
    }

    return 0;

}
