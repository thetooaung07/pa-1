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
    int nameCount;
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


void createStudent(STUDENT *student, const int *studentSize, char *inputLine) {

    size_t nameLength = strlen(inputLine + 3);
    student[*studentSize].name = (char *) malloc((nameLength + 1) * sizeof(char));
    strcpy(student[*studentSize].name, inputLine + 3);

    student[*studentSize].isPresent = false;
    student[*studentSize].isRegister = false;

    size_t nameArrCapacity = 3;
    student[*studentSize].nameArr = (char **) malloc(nameArrCapacity * sizeof(char *));


    char *tempLine = strdup(inputLine + 3);
    char *token;
    token = strtok(tempLine, " ");
    int tokenCount = 0;

    while (token != NULL) {
        student[*studentSize].nameArr[tokenCount] = (char *) malloc((strlen(token) + 1) * sizeof(char));
        strcpy(student[*studentSize].nameArr[tokenCount], token);

        token = strtok(NULL, " ");
        tokenCount++;

        if (tokenCount >= nameArrCapacity) {
            nameArrCapacity *= 2;
            student[*studentSize].nameArr = (char *) realloc(
                    student[*studentSize].nameArr,
                    nameArrCapacity * sizeof(char *));
        }

    }


    student[*studentSize].nameCount = tokenCount;

    qsort(student[*studentSize].nameArr, tokenCount, sizeof(char *),
          (int (*)(const void *, const void *)) charCompare);

    free(tempLine);
}

void freeStudent(STUDENT *student, int *studentSize) {

    for (int i = 0; i < (*studentSize); ++i) {
        free(student[i].name);
        for (int j = 0; j < student[i].nameCount; ++j) {
            free(student[i].nameArr[j]);
        }
        free(student[i].nameArr);
    }
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

            if (rStudentSize >= rStudentCapacity) {
                rStudentCapacity *= 2;
                rStudent = (STUDENT *) realloc(rStudent, rStudentCapacity * sizeof(STUDENT));
            }
            createStudent(rStudent, &rStudentSize, inputLine);
            rStudent[rStudentSize].isRegister = true;
            rStudentSize++;
        } else if (operation == 'P') {

            if (pStudentSize >= pStudentCapacity) {
                pStudentCapacity *= 2;
                pStudent = (STUDENT *) realloc(pStudent, pStudentCapacity * sizeof(STUDENT));
            }
            createStudent(pStudent, &pStudentSize, inputLine);
            pStudent[pStudentSize].isPresent = true;

            pStudentSize++;
        }

    }


    for (int i = 0; i < rStudentSize; ++i) {

        printf("i loop - %s\n", rStudent[i].name);


        for (int j = 0; j < pStudentSize; ++j) {
            printf("j loop - %s\n", pStudent[j].name);
            bool samePerson = false;

            if (rStudent[i].nameCount != pStudent[j].nameCount || pStudent[j].isRegister == true) {
                samePerson = false;

            } else {
                for (int k = 0; k < rStudent[i].nameCount; ++k) {
                    printf("Strcasecmp check - %s vs %s \n", rStudent[i].nameArr[k], pStudent[j].nameArr[k]);
                    if (strcasecmp(rStudent[i].nameArr[k], pStudent[j].nameArr[k]) == 0) {
                        samePerson = true;
                    } else {
                        samePerson = false;
                        break;
                    }

                }
            }


            if (samePerson == true) {
                printf("Same Person  - %s %s\n", rStudent[i].name, pStudent[j].name);
                rStudent[i].isPresent = true;
                pStudent[j].isRegister = true;
                break;
            } else {
                printf("Different Person  - %s %s \n", rStudent[i].name, pStudent[j].name);
            }

        }

        printf("\n\n");
    }


    printf("Not Present:\n");
    for (int i = 0; i < rStudentSize; ++i) {
        if (rStudent[i].isRegister == true && rStudent[i].isPresent == false) {
            printf("* %s\n", rStudent[i].name);
        }
    }

    printf("Without Registration:\n");
    for (int i = 0; i < pStudentSize; ++i) {
        if (pStudent[i].isRegister == false && pStudent[i].isPresent == true) {
            printf("* %s\n", pStudent[i].name);
        }
    }


    if (!feof(stdin)) {
        free(inputLine);
        freeStudent(rStudent, &rStudentSize);
        freeStudent(pStudent, &pStudentSize);
        free(pStudent);
        free(rStudent);
        return EXIT_FAILURE;
    }

    free(inputLine);
    freeStudent(rStudent, &rStudentSize);
    freeStudent(pStudent, &pStudentSize);
    free(pStudent);
    free(rStudent);
    return EXIT_SUCCESS;

}

