#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct TStudent {
    char *name;
    char **nameArr;
    bool isRegister;
    bool isPresent;
    int position;
} STUDENT;


void removeNL(char *x) {
    size_t l = strlen(x);
    if (l > 0 && x[l - 1] == '\n') {
        x[l - 1] = 0;
    }
}


int charCompare(char **a, char **b) {
    return strcasecmp(*a, *b);
}


void createStudent(STUDENT *student, int *studentSize, int *studentCap,  char *inputLine) {

    // check alloc
    if((*studentCap) < (*studentSize) ){
        (*studentCap) *= 2;
        student = (STUDENT *) realloc(student, (*studentCap) * sizeof(STUDENT));
    }

    // init
    size_t nameLength = strlen(inputLine + 3);
    student[*studentSize].name = (char *) malloc(nameLength * sizeof(char));
    strcpy(student[*studentSize].name, inputLine + 3);

    student[*studentSize].position = *studentSize;
    student[*studentSize].isPresent = false;
    student[*studentSize].isRegister = false;

    student[*studentSize].nameArr = (char **) malloc(10 * sizeof(char *));

    char *token;
    token = strtok(inputLine + 3, " ");
    int tokenCount = 0;


    while (token != NULL) {
        student[*studentSize].nameArr[tokenCount] = (char *) malloc(strlen(token) + 1 * sizeof(char));
        strcpy(student[*studentSize].nameArr[tokenCount], token);
        token = strtok(NULL, " ");
        tokenCount++;
    }

    qsort(student[*studentSize].nameArr, tokenCount, sizeof(char *),
          (int (*)(const void *, const void *)) charCompare);

}


int main() {

    char *inputLine = NULL;
    size_t input = 0;
    char operation = 0;
    int rStudentSize = 0;
    int pStudentSize = 0;

    STUDENT *rStudent, *pStudent;
    int rStudentCapacity = 10, pStudentCapacity = 10;
    rStudent = (STUDENT *) malloc(rStudentCapacity * sizeof(STUDENT));
    pStudent = (STUDENT *) malloc(pStudentCapacity * sizeof(STUDENT));

    printf("Students:\n");

    while (getline(&inputLine, &input, stdin) != -1) {
        removeNL(inputLine);
        operation = inputLine[0];

        if (operation == 'R') {
   createStudent(rStudent, &rStudentSize, &rStudentCapacity ,inputLine);
            rStudent[rStudentSize].isRegister = true;
            rStudentSize++;
        } else if (operation == 'P') {
            createStudent(pStudent, &pStudentSize, &pStudentCapacity,inputLine);
            rStudent[rStudentSize].isPresent = true;
        }

    }


    printf("Not present:\n");
    for (int i = 0; i < rStudentSize; ++i) {
        if (rStudent[i].isPresent == false) {
            printf("* %s\n", rStudent[i].name);
        }
    }


    printf("Without registration:\n");
    for (int i = 0; i < rStudentSize; ++i) {
        if (rStudent[i].isRegister == false && rStudent[i].isPresent == true) {
            printf("* %s\n", rStudent[i].name);
        }
    }

    if (!feof(stdin)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;

}
