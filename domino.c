#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

typedef struct Domino {
    char id;
    int *numbers;
    char *duplicateIds;
    int totalSum;
    int noOfElement;
    bool hasDuplicate;
    int duplicateCount;
    int duplicateTag;
} Domino;


Domino *initializeArray(Domino *domino, int *index, int *capacity, char id) {
    if (*index >= *capacity) {
        *capacity *= 2;
        domino = (Domino *) realloc(domino, ((*capacity) * sizeof(Domino)));
    }

    domino[*index].id = id;
    domino[*index].duplicateIds = (char *) malloc(sizeof(char));
    domino[*index].numbers = NULL;
    domino[*index].totalSum = 0;
    domino[*index].hasDuplicate = false;
    domino[*index].duplicateCount = 0;
    domino[*index].duplicateTag = -1;

    return domino;

}


Domino *pushToArray(Domino *domino, int *index, int number, int *numberIndex,
                    int *capacity) {

    if ((*numberIndex) == 0) {
        domino[*index].numbers = (int *) malloc((*capacity) * sizeof(int));
    }

    if (*numberIndex >= *capacity) {
        (*capacity) *= 2;
        domino[*index].numbers = (int *) realloc(domino[*index].numbers,
                                                 (*capacity) * sizeof(int));
    }

    domino[*index].numbers[*numberIndex] = number;
    domino[*index].totalSum = domino[*index].totalSum + number;
    domino[*index].noOfElement = (*numberIndex) + 1;
    return domino;

}

int main() {

    char id;
    char checked = 'a';
    char open_bracket;
    int arrIndex = 0;
    int dominoCapacity = 10;
    int duplicateTag = 100;

    Domino *domino = (Domino *) malloc(arrIndex * sizeof(Domino));

    printf("Domino\n");

    while (scanf(" %c %c", &id, &open_bracket) == 2 && id == checked &&
           open_bracket == '[') {

        domino = initializeArray(domino, &arrIndex, &dominoCapacity, id);
        int numIndex = 0;
        int numArrCapacity = 10;

        while (1) {
            int inputNum = 0;
            char end = 0;
            if (scanf(" %d %c", &inputNum, &end) != 2 ||
                (end != ',' && end != ']')) {

            }

            pushToArray(domino, &arrIndex, inputNum, &numIndex,
                        &numArrCapacity);

            numIndex++;

            if (end == ']') {
                break;
            }
        }

        arrIndex++;
        checked++;


    }

    for (int i = 0; i < arrIndex; ++i) {
        for (int j = i + 1; j < arrIndex; ++j) {
            if (domino[i].noOfElement != domino[j].noOfElement) { continue; }

            int ssIndex = -1;

            for (int k = 0; k < domino[j].noOfElement; ++k) {
                if (domino[i].numbers[0] == domino[j].numbers[k]) {
                    ssIndex = k;
                    break;
                }
            }

            if (ssIndex == -1) { continue; }
            int isDuplicate = false;

            for (int first = 0, second = ssIndex;
                 first < domino[j].noOfElement; first++, ++second) {

                if (second >= domino[j].noOfElement) {
                    second = 0;
                }
                if (domino[i].numbers[first] !=
                    domino[j].numbers[second]) {
                    isDuplicate = false;
                    break;
                } else {
                    isDuplicate = true;
                }
            }


            if (isDuplicate == true) {

                printf("This is exec add - %c to %c \n", domino[j].id,
                       domino[i].id);


                printf("char id %c -%c - %d\n", domino[i].id, domino[j].id,
                       duplicateTag);
                if (domino[i].duplicateTag == -1) {
                    domino[i].duplicateTag = duplicateTag + 10;
                }

                domino[j].duplicateTag = domino[i].duplicateTag;


                duplicateTag++;

                domino[i].hasDuplicate = true;
                domino[j].hasDuplicate = true;


                domino[j].duplicateCount++;
                domino[i].duplicateCount++;


                domino[i].duplicateIds = (char *) realloc(
                        domino[i].duplicateIds,
                        domino[i].duplicateCount * sizeof(char));


                printf("%c is added at index -%d\n", domino[j].id,
                       domino[i].duplicateCount - 1);

                domino[i].duplicateIds[domino[i].duplicateCount -
                                       1] = domino[j].id;
            }

        }
    }


    for (int i = 0; i < arrIndex; ++i) {
        printf("no of el = %d\n", domino[i].noOfElement);
        printf("%c [", domino[i].id);
        for (int j = 0; j < domino[i].noOfElement; ++j) {
            printf("%d ", domino[i].numbers[j]);
        }
        printf("]\n");

        printf("duplicated Counts  - %d , has duplicate %d",
               domino[i].duplicateCount, domino[i].hasDuplicate);

        printf("DuplicateTag %d\n", domino[i].duplicateTag);
        for (int j = 0; j < domino[i].duplicateCount; ++j) {
            printf("%c -", domino[i].duplicateIds[j]);
        }
        printf("\n");

    }

    int max = 0;
    for (int i = 0; i < arrIndex; ++i) {
        if (domino[i].duplicateCount > max) {
            max = domino[i].duplicateCount;
        }
    }

    printf("Max - %d", max + 1);

    for (int i = 0; i < arrIndex; i++) {
        free(domino[i].numbers);
        free(domino[i].duplicateIds);
    }

    if (!feof(stdin)) {
        free(domino);
        return EXIT_SUCCESS;
    }

    free(domino);
    return EXIT_SUCCESS;
}
