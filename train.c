//
// Created by aungthet on 2/4/24.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"


typedef struct Train {
    char companyName[4097];
    int dh, dm, ds, ah, am, as;
    int convertedArv, convertedDep;
} Train;


bool validateTime(int hour, int min, int sec) {
    if (hour < 0 || min < 0 || min > 59 || sec < 0 || sec > 59) {
        printf("error ");
        return false;
    }


    return true;
}

bool validateTimeDuration(int dh, int dm, int ds, int ah, int am, int as) {
    if (ah < dh) { return false; }
    if (ah == dh && am < dm) { return false; }
    if (ah == dh && am == dm && as < ds) { return false; }
    else return true;
}

bool checkInput(int dh, int dm, int ds, int ah, int am, int as, char companyName[4097]) {

    int nameL = strlen(companyName);

    if (companyName[nameL - 1] == ' ') {
        printf("x name contains space in the end\n");
        return false;
    }

    for (int i = 0; i < nameL; ++i) {
        if (companyName[i] != ' ' && (!isalpha(companyName[i]) && companyName[i] != '_')) {
            printf("x name error\n");
            return false;
        }
    }


    if (validateTime(dh, dm, ds) == false) { return false; }
    if (validateTime(ah, am, as) == false) { return false; }
    if (validateTimeDuration(dh, dm, ds, ah, am, as) == false) { return false; }

    return true;
}

int convertToSec(int hour, int min, int sec) {
    return (hour * 3600) + (min * 60) + sec;
}

Train *push_array(Train *tr, int *size, int *capacity, int dh, int dm, int ds, int ah, int am, int as,
                  char companyName[4097]) {


    if (*size >= *capacity) {
        *capacity *= 2;
        tr = (Train *) realloc(tr, *capacity * sizeof(Train));
    }

    tr[*size].dh = dh;
    tr[*size].dm = dm;
    tr[*size].ds = ds;
    tr[*size].ah = ah;
    tr[*size].am = am;
    tr[*size].as = as;
    tr[*size].convertedDep = convertToSec(dh, dm, ds);
    tr[*size].convertedArv = convertToSec(ah, am, as);
    strcpy(tr[*size].companyName, companyName);

    printf("Push to array %d\n", *size);

    (*size)++;


    return tr;
}

void print_result(Train *trA, int aSize, Train *trB, int bSize, int time) {
    if (!trA || !trB || aSize == 0 || bSize == 0) {
        return;
    }

    Train *bestA, *bestB;


    for (int i = 0; i < aSize; ++i) {
        if (time <= trA[i].convertedDep) {
            bestA = trA[i];

            for (int j = 0; j < bSize; ++j) {
                if (trB->convertedDep >= bestA->convertedArv) {
                    bestB = trB[j];
                }
            }
        }
    }
}

int arrivalCmp(const void *x, const void *y) {
    Train *t1 = (Train *) x;
    Train *t2 = (Train *) y;

    return (t1->convertedArv - t2->convertedArv);
}


int main() {

    printf("Start.\n");

    char option = '\0';
    bool inputComplete = false;

    int aSize = 0;
    int aCapacity = 10;
    Train *trA = (Train *) malloc(aCapacity * sizeof(Train));


    int bSize = 0;
    int bCapacity = 10;
    Train *trB = (Train *) malloc(bCapacity * sizeof(Train));

    int isSorted = 0;


    while (scanf(" %c", &option) == 1) {

        if (inputComplete == true && (option == 'A' || option == 'B')) {
            printf("No more inputs accept.\n");
            continue;
        }


        if (option == 'A') {
            int dh, dm, ds, ah, am, as;
            char companyName[4097];
            if (scanf("%d:%d:%d %d:%d:%d %4096[^\n]", &dh, &dm, &ds, &ah, &am, &as, companyName) != 7) {
                printf("x Invalid scanf\n");
            }


            if (checkInput(dh, dm, ds, ah, am, as, companyName) == false) {
                printf("x Invalid checkInput.\n");
                continue;
            }

            trA = push_array(trA, &aSize, &aCapacity, dh, dm, ds, ah, am, as, companyName);

        } else if (option == 'B') {
            int dh, dm, ds, ah, am, as;
            char companyName[4097];
            if (scanf("%d:%d:%d %d:%d:%d %4096[^\n]", &dh, &dm, &ds, &ah, &am, &as, companyName) != 7) {
                printf("x Invalid scanf\n");
            }

            if (checkInput(dh, dm, ds, ah, am, as, companyName) == false) {
                printf("x Invalid checkInput.\n");
                continue;
            }

            trB = push_array(trB, &bSize, &bCapacity, dh, dm, ds, ah, am, as, companyName);
        } else if (option == '?') {
            inputComplete = true;
            int hour, min, sec;
            scanf("%d:%d:%d", &hour, &min, &sec);
            int time = convertToSec(hour, min, sec);

            if (isSorted == 0) {
                qsort(trA, aSize, sizeof(trA[0]), arrivalCmp);
                qsort(trB, bSize, sizeof(trB[0]), arrivalCmp);
            }
            print_result(trA, aSize, trB, bSize, time);

        }
    }

    if (!feof(stdin)) {
        return 0;
    }

    return EXIT_SUCCESS;
}