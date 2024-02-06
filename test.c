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

// Max Sub Array problem

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


int factorialRec(int n) {
    if (n <= 1) return 1;
    return n * factorialRec(n - 1);
}


// gcd (recursive)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int gcd_iter(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int fibonaci(int n) {
    if (n < 2) { return 1; }
    return fibonaci(n - 1) + fibonaci(n - 2);
}

void factorize(int x) {
    int d = 2;
    while (d <= x) {
        if (x % d == 0) {
            printf("%d-", d);
            factorize(x / d);
            return;
        } else d++;
    }
}

// ordinary merge function
void merge(int *a, int na, int *b, int nb, int *c) {
    int ia = 0;
    int ib = 0;
    int ic = 0;
    while (ia < na && ib < nb) {
        if (a[ia] < b[ib]) {
            c[ic] = a[ia];
            ic++;
            ia++;
        } else {
            c[ic] = b[ib];
            ic++;
            ib++;
        }
        while (ia < na) {
            c[ic] = a[ia];
            ia++;
            ic++;

        }
        while (ib < nb) {
            c[ic] = b[ib];
            ic++;
            ib++;
        }
    }
}


// merge sort => merge
void mergeS(int *src, int *dst, int l, int r, int rEnd) {
    int lEnd = r - 1, i = l;
    while (l <= lEnd && r <= rEnd) {
        dst[i++] = (src[l] < src[r]) ? src[l++] : src[r++];
    }
    while (l <= lEnd) dst[i++] = src[l++];
    while (r <= rEnd) dst[i++] = src[r++];
}

void mergeSortRec(int *a, int *temp, int l, int r) {
    int mid;
    if (l == r) return;
    mid = l + (r - l) / 2;
    mergeSortRec(a, temp, l, mid);
    mergeSortRec(a, temp, mid + 1, r);
    mergeS(a, temp, l, mid + 1, r);
    for (int i = l; i <= r; ++i) {
        a[i] = temp[i];
    }
}

//int intCmp(const int *a, const int *b) {
//    return (*b < *a) - (*a < *b);
//}
//
//void qsortFunc() {
//    int *arr;
//    int n; // numberof element in array
//
//    qsort(arr, n, sizeof(int), (int (*)(const void *, const void *)) intCmp);
//}

void mergeSort(int *a, int n) {
    int *temp = (int *) malloc(n * sizeof(int));
    mergeSortRec(a, temp, 0, n - 1);
    free(temp);
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


    factorize(40);
}