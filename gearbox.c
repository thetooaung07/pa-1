//
// Created by Thet Oo Aung on 02/02/2024.
//
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"


typedef struct Wheel {
    int tooth_count;
    char company[4097];
} Wheel;


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

Wheel *push_arr(Wheel *wh, int *size, int *capacity, int tooth_count,
                char company[4096]) {

    if (*size >= *capacity) {
        *capacity *= 2;
        wh = (Wheel *) realloc(wh, *capacity * sizeof(Wheel));
    }

    strcpy(wh[*size].company, company);
    wh[*size].tooth_count = tooth_count;

//    printf("Company %s\n", wh[*size].company);
//    printf("Tooth Count %d\n", wh[*size].tooth_count);

    (*size)++;
    return wh;
}


/*
+ 40 toa
+ 24 toa

*/

int getGreater(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

int getSmaller(int num1, int num2) {
    return (num1 > num2) ? num2 : num1;
}

void print_result(int gcd, int b_ratio, int s_ratio, int b_tc, int s_tc) {

    if (gcd * b_ratio == b_tc && gcd * s_ratio == s_tc) {
        printf("%d - %d \n", b_tc, s_tc);
    }
}

void find_gear(Wheel *wh, int size, int ratio1, int ratio2) {


    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {

            if (strcmp(wh[i].company, wh[j].company) != 0) { return; }

            int b_tc = getGreater(wh[i].tooth_count, wh[j].tooth_count);
            int s_tc = getSmaller(wh[i].tooth_count, wh[j].tooth_count);
            int gcdRes = gcd(wh[i].tooth_count, wh[j].tooth_count);


            if (ratio1 > ratio2) {
                print_result(gcdRes, ratio1, ratio2, b_tc, s_tc);
            } else if (ratio2 > ratio1) {
                print_result(gcdRes, ratio2, ratio1, b_tc, s_tc);
            }

        }
    }

}


int main() {

    int capacity = 10;
    int size = 0;

    Wheel *wh = (Wheel *) malloc(capacity * sizeof(Wheel));
    printf("%ld\n", gcd(51, 36));
    printf("%ld\n", gcd(40, 24));
    printf("Gears:\n");

    char operation = '\0';

    while (scanf(" %c", &operation) != EOF) {

        if (operation == '+') {
            int tooth_count;
            char company[4097];
            scanf(" %d %4096[^\n]", &tooth_count, company);
            wh = push_arr(wh, &size, &capacity, tooth_count, company);


        } else if (operation == '?') {
            int ratio1, ratio2;
            int count;
            scanf(" %d:%d,%d", &ratio1, &ratio2, &count);

            find_gear(wh, size, ratio1, ratio2);


        }
    }

    free(wh);

    return EXIT_SUCCESS;

//    for (int i = 0; i < size; ++i) {
//                printf("%d- Tc %d , cmp - %s\n", i, wh[i].tooth_count,
//                       wh[i].company);
//            }
}
