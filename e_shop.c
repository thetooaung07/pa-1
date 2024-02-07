//
// Created by Thet Oo Aung on 06/02/2024.
//


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "limits.h"

typedef struct Review {
    int year, month, day;
    int rating;
    char review[4097];
} Review;

typedef struct ReviewStats {
    int startIndex, endIndex;
    int totalRating;
    int size;

} ReviewStats;

int isLeapYear2(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) &&
            year % 4000 != 0);
}


int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) &&
            year % 4000 != 0);
}

bool checkDate(int year, int month, int day) {


    int yearArr[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year)) {
        yearArr[2] = 29;
    }

    if (yearArr[month] < day) {
        return false;
    }

    return true;
}


bool check_input(int year, int month, int day, int rating,
                 char review[4097]) {
    if (year < 1800 || year > 3000 || month < 0 || month > 12 || day < 0 ||
        day > 31) {
        return false;
    }

    if (checkDate(year, month, day) == false) {
        return false;
    }

    if (rating < 0) {
        return false;
    }
    if (strlen(review) == 0) {
        return false;
    }

    return true;

}

Review *
push_array(Review *arr, int *size, int *cap, int year, int month, int day,
           int rating,
           char review[4097]) {

    if (*size >= *cap) {
        *cap *= 2;
        arr = (Review *) realloc(arr, *cap * sizeof(Review));
    }

    arr[*size].year = year;
    arr[*size].month = month;
    arr[*size].day = day;
    arr[*size].rating = rating;
    strcpy(arr[*size].review, review);
    (*size)++;

    return arr;

}


bool sameDate(Review rev1, Review rev2) {

    if (rev1.day == rev2.day && rev1.month == rev2.month &&
        rev1.day == rev2.day) {
        return true;
    }

    return false;
}

ReviewStats *
print_reviews(Review *arr, int size, ReviewStats *rsArr, int *rsSize,
              int *rsCap,
              int queryAmount) {


    int startIndex = 0;
    for (int i = 0; i < size; ++i) {


        if (sameDate(arr[i], arr[i + 1]) == true) {
            continue;
        }

        rsArr[*rsSize].startIndex = startIndex;
        rsArr[*rsSize].endIndex = i;

        rsArr[*rsSize].size = i - startIndex + 1;
        (*rsSize)++;

        if (*rsSize >= *rsCap) {
            *rsCap *= 2;
            rsArr = (ReviewStats *) realloc(rsArr,
                                            *rsCap * sizeof(ReviewStats));
        }


    }


//    for (int i = 0; i < size; ++i) {
//        printf("i loop %d\n", i);
//        for (int j = i + 1; j < size - 1; ++j) {
//            printf("\tj loop%d\n", j);
//
//
//            if (i == 0) { continue; }
//            if (j == size - 1) { continue; }
//            if (sameDate(arr[i], arr[j + 1]) == true) {
//                continue;
//            }
//
//
//            printf("different %d %d \n", arr[i].day, arr[j + 1].day);
//
//            rsArr[*rsSize].startIndex = i;
//            rsArr[*rsSize].endIndex = j;
//            rsArr[*rsSize].size = j - i + 1;
//            (*rsSize)++;
//
//            if (*rsSize >= *rsCap) {
//                *rsCap *= 2;
//                rsArr = (ReviewStats *) realloc(rsArr,
//                                                *rsCap * sizeof(ReviewStats));
//            }
//            i = j + 1;
//
//        }
//    }
    printf("final rsSize - %d \n", *rsSize);

    for (int i = 0; i < *rsSize; ++i) {

        for (int j = rsArr[i].startIndex; j <= rsArr[i].endIndex; ++j) {
            rsArr[i].totalRating += arr[j].rating;
        }

        printf("tr- %d startIndex %d endIndex %d\n", rsArr[i].totalRating,
               rsArr[i].startIndex, rsArr[i].endIndex);
    }

    return rsArr;


}

int main() {


    int size = 0, rsSize = 0;
    int cap = 10;
    int rsCap = 10;
    Review *revArr = (Review *) malloc(cap * sizeof(Review));
    ReviewStats *rsArr = (ReviewStats *) malloc(rsCap * sizeof(ReviewStats));
    char option;

    while (scanf(" %c", &option) == 1) {


        int year, month, day;
        int rating;
        char review[4097];
        if (option == '+') {
            if (scanf("%d-%d-%d %d %4096s", &year, &month, &day,
                      &rating,
                      review) != 5) {
                printf("Input Invalid input.\n");
                free(revArr);
                return EXIT_FAILURE;
            }

            if (check_input(year, month, day, rating, review) ==
                false) {
                printf("Check Input Invalid input.\n");
                free(revArr);
                return EXIT_FAILURE;
            }

            revArr = push_array(revArr, &size, &cap, year, month, day, rating,
                                review);


        } else if (option == '?' || option == '#') {
            int queryAmount = 0;
            if (scanf("%d", &queryAmount) != 1) {
                printf("? scanf Invalid input.\n");
                free(revArr);
                return EXIT_FAILURE;
            }
            if (queryAmount <= 0) {
                printf("review amount  <= 0\n");
                free(revArr);
                return EXIT_FAILURE;
            }
            rsArr = print_reviews(revArr, size, rsArr, &rsSize, &rsCap,
                                  queryAmount);

        } else {
            free(revArr);
            return EXIT_FAILURE;
        }


    }


    if (!feof(stdin)) {
        free(revArr);
        return EXIT_FAILURE;
    }

    free(revArr);
    return EXIT_SUCCESS;

}