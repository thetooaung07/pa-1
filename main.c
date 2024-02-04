#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "stdlib.h"
#include <stdbool.h>
#include "float.h"
#include "string.h"


int main(void) {


//    int array2D[4][4] = {
//            {1,  2,  3,  4},
//            {5,  6,  7,  8},
//            {9,  10, 11, 12},
//            {13, 14, 15, 16},
//    };
//    int array1D[16] = {
//            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
//    };
//
//    memset(array2D, 0, sizeof array2D);


    size_t m = 4, n = 4;
    int **array2d = (int **) malloc(m * sizeof(int *));


    for (size_t i = 0; i < n; i++) {
        array2d[i] = (int *) malloc(n * sizeof(int));
    }


    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            array2d[i][j] = i * n + j + 1;


    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("%d", array2d[i][j]);
        }
        printf("\n");
    }


    return 0;
}
