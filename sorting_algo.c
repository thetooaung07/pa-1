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
    do {
        sorted = 1;
        for (int i = 0; i < n - 1; ++i) {
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

void insertion_sort(int *a, int n) {
    int key, j;

    for (int i = 1; i < n; ++i) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}


void merge_sort() {

}


void print_arr(int arr[], int n) {
    printf("Number  n = %d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d-", arr[i]);

    }
    printf("\n");
}


// O(n^3)
int max_sum_brute_force(int *a, int n) {
    int maxSum = 0;
    int startIndex = 0;
    int length = 0;


    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int sum = 0;
            for (int k = i; k < j; ++k) {
                sum += a[k];
            }
            if (sum > maxSum) {
                maxSum = sum;
                startIndex = i;
                length = j - i + 1;
            }
        }
    }
    return maxSum;
}

// O(n^2)
int maxSum2(int *a, int n) {
    int maxSum = 0;
    int startIndex = 0;
    int length = 0;


    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = i; j < n; ++j) {
            sum += a[j];
            if (sum > maxSum) {
                maxSum = sum;
                startIndex = i;
                length = j - i + 1;
            }
        }
    }
    return maxSum;
}

// O^n - linear solution
int maxSum(int *a, int n) {
    int maxSum = 0;
    int sum = 0;
    int s = 0;
    int startIndex = 0;
    int length = 0;

    for (int i = 0; i < n; ++i) {
        sum += a[i];
        if (sum > maxSum) {
            startIndex = s;
            length = i - s + 1;
            maxSum = sum;
        }
        if (sum < 0) {
            s = i + 1;
            sum = 0;
        }
    }
    return maxSum;
}

// sorting
int main() {
    int arr[] = {2, 4, 3, 6, 10, 55, 22};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    //for max-sum problem
    int a[] = {-2, 11, -4, 13, -5, 2};
    int n = sizeof(a) / sizeof(a[0]);
    int result = max_sum_brute_force(a, n);
    int result2 = maxSum2(a, n);
    int result3 = maxSum(a, n);
    printf("max sum - %d\n", result);
    printf("max sum - %d\n", result2);
    printf("max sum - %d\n", result3);


    bubble_sort(arr, arrSize);
    print_arr(arr, arrSize);

    select_sort(arr, arrSize);
    print_arr(arr, arrSize);

    insertion_sort(arr, arrSize);
    print_arr(arr, arrSize);

}