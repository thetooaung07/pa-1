#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct TStudent {
    char *name;
    char **nameArr;
    bool isPresent;
    bool isRegister;

} STUDENT;


int main() {

    char *inputLine = NULL;
    size_t input = 0;
    char operation = 0;
    int studentCapacity = 10;
    int inputArrSize = 0;

    STUDENT *student;
    student = (STUDENT *) malloc(studentCapacity * sizeof(STUDENT));

    printf("Students:\n");

    while (getline(&inputLine, &input, stdin) != -1) {


        student->nameArr = (char *)malloc(10, sizeof (char));

        if (inputArrSize == studentCapacity) {
            studentCapacity *= 2;
            student = (STUDENT *) realloc(student, studentCapacity);
        }
        if (operation == 'P' && inputLine[0] == 'R') {
            printf("R after P error\n");
            return EXIT_FAILURE;
        }

        operation = inputLine[0];


        size_t inputLineSize = strlen(inputLine);


        if (operation == 'R') {
            for (int i = 3; i < inputLineSize; ++i) {
                if (inputLine[i] == ' ') {
                    break();
                }

            }

        } else if (operation == 'P') {

        }
        inputArrSize++;
    }

    if (!feof(stdin)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;

}