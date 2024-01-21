#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define max 10

typedef struct parking_space {
    int floor;
    int position;
    bool occupy;
    char car_number[max + 1];
} Parking;


void removeNL(char *l) {
    int x = strlen(l);
    if (x > 0 && l[x - 1] == '\n') {
        l[x - 1] = '\0';
    }
}

Parking *push_array(Parking *arr, int *index, int *capacity, int floor, int position, char car_number[11]) {


    // occupy - false reassign


    // realloc
    if (*index >= *capacity) {
        *capacity *= 2;
        arr = (Parking *) realloc(arr, (*capacity) * sizeof(Parking));
    }

    arr[*index].floor = floor;
    arr[*index].position = position;
    arr[*index].occupy = true;
    strcpy(arr[*index].car_number, car_number);
    printf("OK\n");

    return arr;

}


bool check_input(Parking *arr, int index, int floor, int position, char car_number[], int max_floor, int max_position) {
    if (floor < 0 || floor > max_floor - 1) return false;
    if (position < 0 || position > max_position - 1) return false;


    for (int i = 0; i < index; ++i) {
        if (arr[i].floor == floor && arr[i].position == position && arr[i].occupy == true) {
            printf("Occupied by %s\n", arr[i].car_number);
            return false;
        }
    }
    return true;

}

void find_car(Parking *arr, int parkingIndex, char car_number[11]) {

    printf("index  - %d", parkingIndex);

    for (int i = 0; i < parkingIndex; ++i) {

        printf("cn: %s c1: %s %d\n", arr[i].car_number, car_number, arr[i].occupy);
        if (strcmp(arr[i].car_number, car_number) == 0 && arr[i].occupy == true) {
            arr[i].occupy = false;
//            strcpy(arr[i].car_number, "");
            printf("OK\n");
            return;
        }
    }

    printf("Not found\n");
    // not found -

}

int main() {


    int max_floor = 10;
    int max_position = 20;
   
    printf("Size:\n");
    if (scanf("%d %d", &max_floor, &max_position) != 2 || max_floor < 1 || max_position < 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }


    int parkingIndex = 0;
    int parkingCapacity = 10;

    Parking *ps = (Parking *) malloc(parkingCapacity * sizeof(Parking));

    printf("Requirements:\n");

    char operation = '\0';

    while (scanf(" %c", &operation) == 1) {

//        init ps[i]
        ps[parkingIndex].occupy = false;


//        + add
        if (operation == '+') {

            int floor;
            int position;
            char car_number[11];
            scanf("%d %d %10[^\n]", &floor, &position, car_number);
            if (check_input(ps, parkingIndex, floor, position, car_number, max_floor, max_position)) {
                ps = push_array(ps, &parkingIndex, &parkingCapacity, floor, position, car_number);
                parkingIndex++;
            } else {
                free(ps);
                printf("Invalid input.\n");
                return EXIT_FAILURE;
            }


        } else if (operation == '-') {
            char car_number[11];
            scanf(" %10s", car_number);
            find_car(ps, parkingIndex, car_number);


        } else {
            free(ps);
            printf("Invalid input.1\n");
            return EXIT_FAILURE;
        }

    }

    //        FEOF
    if (!feof(stdin)) {

        free(ps);
        return EXIT_SUCCESS;
    }


    free(ps);
    return EXIT_SUCCESS;
}