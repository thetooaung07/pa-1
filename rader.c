//
// Created by Thet Oo Aung on 31/01/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct airplane {
    double x;
    double y;
    char name[199 + 1];
} airplane;

airplane *
push_to_array(airplane *arr, int *size, int *capacity, double x, double y,
              char name[200]) {

    if (*size >= *capacity) {
        *capacity *= 2;
        arr = (airplane *) realloc(arr, *capacity * sizeof(airplane));
    }

    arr[*size].x = x;
    arr[*size].y = y;
    strcpy(arr[*size].name, name);
    (*size)++;

    return arr;
}

void print_arr(airplane *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("|%lf|%lf| -> %s\n", arr[i].x, arr[i].y, arr[i].name);
    }
}

int main() {

    int capacity = 10;
    int size = 0;
    airplane *ap;

    ap = (airplane *) malloc(capacity * sizeof(airplane));


    printf("Plane coordinates:\n");


    double x, y;
    char name[200];

    while (scanf("%lf,%lf: %199s", &x, &y, name) == 3) {
        ap = push_to_array(ap, &size, &capacity, x, y, name);

    }

    print_arr(ap, size);


    if (!feof(stdin)) {
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
