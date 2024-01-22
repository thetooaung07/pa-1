//
// Created by aungthet on 1/22/24.
//


#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct work_load {
    int load;
    int start;
    int end;
} Workload;

int main() {

    Workload *wl;
    int size = 0;
    int capacity = 10;

    wl = (Workload *) malloc(capacity * sizeof(Workload));

    printf("Load:\n");

    int load = 0;
    int start = 0;
    int end = 0;
    int max = 0;


    while (scanf("%d: %d..%d", &load, &start, &end) == 3) {
        wl[size].load = load;
        wl[size].start = start;
        wl[size].end = end;
        if (end > max) max = end;
        size++;
        if (size >= capacity) {
            capacity *= 2;
            wl = (Workload *) realloc(wl, capacity * sizeof(Workload));
        }
    }

    int *resultArr = (int *) calloc(max, sizeof(int));

    for (int i = 0; i < size; ++i) {
        for (int j = wl[i].start; j < wl[i].end; ++j) {
            resultArr[j] += wl[i].load;
        }
    }

    int highestLoad = 0;

    for (int i = 0; i < max; ++i) {
        if (resultArr[i] > highestLoad) { highestLoad = resultArr[i]; }
    }

    printf("Peak Load:%d\n", highestLoad);


    for (int i = 0; i < max; ++i) {
        // start
        if (i == 0 && resultArr[i] == highestLoad) {
            printf("%d..", i);
        } else if (resultArr[i] == highestLoad && resultArr[i - 1] < highestLoad) {
            printf("%d..", i);
        }

        // end
        if (i + 1 == max && resultArr[i] == highestLoad) {
            printf("%d\n", i + 1);
        } else if (resultArr[i] == highestLoad && resultArr[i + 1] < highestLoad) {
            printf("%d\n", i + 1);

        }

    }

    if (!feof(stdin)) {
        free(wl);
        free(resultArr);
        return EXIT_SUCCESS;
    }


    free(wl);
    free(resultArr);
    return EXIT_SUCCESS;
}

