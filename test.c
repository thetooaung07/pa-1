#include "stdio.h"
#include "stdlib.h"
#include "string.h"


// Binary-Search
int binarySearch(int arr[], int low, int high, int x) {
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (arr[middle] == x) { return middle; }
        if (arr[middle] < x) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return -1;
}


// qsort - compare
int comp(const void *a, const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x > *y;
}

/*
 * qsort + b-search
int main() {
    int arr[] = {2, 4, 3, 6, 10, 55, 22};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    qsort(arr, arrSize, sizeof(int), comp);

    for (int i = 0; i < arrSize; ++i) {
        printf("%d-", arr[i]);
    }
    printf("\n");

    int result = binarySearch(arr, 0, arrSize - 1, x);
    printf("%d", result);
    printf("\n");
}
 */

int swap_el(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

}

void bubble_sort(int arr[], int n) {
    int sorted;
    printf("B_sort Number  n = %d\n", n);
    do {
        sorted = 1;
        for (int i = 0; i < n - 1; ++i) {
            printf("%d- %d - comparing %d -%d\n", i, n, arr[i], arr[i + 1]);
            if (arr[i] > arr[i + 1]) {
                swap_el(&arr[i], &arr[i + 1]);
                sorted = 0;
            }
        }
        n--;
    } while (sorted == 0);
}


void select_sort(int *a, int n) {

    for (int i = 0; i < n - 1; ++i) {
        int imin = i; // index of the smallest number
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[imin]) imin = j;
            if (imin != i) swap_el(&a[imin], &a[j]);
        }
    }
}

void print_arr(int arr[], int n) {
    printf("Number  n = %d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d-", arr[i]);

    }
    printf("\n");
}

// sorting
int main() {
    int arr[] = {2, 4, 3, 6, 10, 55, 22};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, arrSize);
    print_arr(arr, arrSize);

}