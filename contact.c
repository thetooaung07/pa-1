//
// Created by Thet Oo Aung on 01/02/2024.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ctype.h"

typedef struct Contact {
    char phone_no[21];
    char *name;
    char *nameInT9;
} Contact;

char charToT9(char c) {
    switch (c) {
        case 'a':
        case 'b':
        case 'c':
            return '2';
        case 'd':
        case 'e':
        case 'f':
            return '3';
        case 'g':
        case 'h':
        case 'i':
            return '4';
        case 'j':
        case 'k':
        case 'l':
            return '5';
        case 'm':
        case 'n':
        case 'o':
            return '6';
        case 'p':
        case 'q':
        case 'r':
        case 's':
            return '7';
        case 't':
        case 'u':
        case 'v':
            return '8';
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return '9';
        case ' ':
            return '1';
        default:
            return '0';
    }
}

char *convertT9(char *name) {
    int length = strlen(name);
    char *t9 = (char *) malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i) {
        t9[i] = charToT9(tolower(name[i]));
    }
    t9[length] = '\0';
    return t9;
}

Contact *
push_array(Contact *arr, int *size, int *capacity, char phoneNumber[21],
           char *name) {

    if (*size >= *capacity) {
        if (*capacity == 0) (*capacity)++;
        *capacity *= 2;
        arr = (Contact *) realloc(arr, *capacity * sizeof(Contact));
    }

    int length = strlen(name);
    arr[*size].name = (char *) malloc((length + 1) * sizeof(char));
    strcpy(arr[*size].name, name);
    strcpy(arr[*size].phone_no, phoneNumber);
    arr[*size].nameInT9 = convertT9(name);
    (*size)++;
    printf("OK\n");
    return arr;
}

bool checkInput(char *input) {
    int length = strlen(input);
    int nameStartIndex = 0;
    int phNumberCount = 0;

    if (input[1] != ' ' || !(isdigit(input[2]))) {
        printf("Error at position 2 and 3.\n");
        return false;
    } else {
        phNumberCount = 0;
        nameStartIndex = 3;
        for (char *i = input + 2; *i != ' '; ++i) {
            if (!(isdigit(*i))) {
                printf("Not digit\n");
                return false;
            } else {
                phNumberCount++;
                nameStartIndex++;
            }
        }
    }

    if (phNumberCount > 20) {
        printf("Phone Count  > 20\n");
        return false;
    }

    if (input[nameStartIndex - 1] != ' ' ||
        !(isalpha(input[nameStartIndex]))) { return false; }
    else {

        while (nameStartIndex < length) {

            if (input[nameStartIndex] != ' ' &&
                !isalpha(input[nameStartIndex])) {

                printf("Name Error\n");
                return false;
            }

            if (nameStartIndex == length - 1 &&
                input[nameStartIndex] == ' ') {
                printf("Last Name Error\n");
                return false;
            }
            nameStartIndex++;
        }
    }
    return true;
}

void removeNL(char *x) {
    int l = strlen(x);
    if (l > 0 && x[l - 1] == '\n') {
        x[l - 1] = '\0';
    }
}


bool search(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;

}

bool isInteger(char *search) {
    int len = strlen(search);

    for (int i = 0; i < len; ++i) {
        if (!isdigit(search[i])) {
            return false;
        }
    }

    return true;
}


int main() {
    printf("Enter Contact Name\n");
    char *buffer = NULL;
    size_t s = 0;


    int size = 0;
    int capacity = 0;
    Contact *contact = NULL;

    while (getline(&buffer, &s, stdin) != EOF) {
        removeNL(buffer);
        char operation = buffer[0];

        if (operation == '+') {

            if (!checkInput(buffer)) {
                printf("Input Check Fails.\n");
                continue;
            }


            char *phoneNumber = strtok(buffer + 2, " ");
            char *name = strtok(NULL, "\0");
            int duplicateFlag = 0;


            for (int i = 0; i < size; ++i) {
                if (strcmp(phoneNumber, contact[i].phone_no) == 0 &&
                    strcmp(name, contact[i].name) == 0) {
                    printf("Duplicate contact.\n");
                    duplicateFlag = 1;
                    break;
                }
            }

            if (duplicateFlag == 0) {
                contact = push_array(contact, &size, &capacity, phoneNumber,
                                     name);
            }
        } else if (operation == '?') {
            char *searchQuery = buffer + 2;
            int count = 0;
            int resultIndex[11];
            int resSize = 0;

            if (*searchQuery == '\0') {
                printf("Empty Search Query\n");
                continue;
            }
            if (isInteger(searchQuery)) {
                for (int i = 0; i < size; ++i) {

                    if (search(contact[i].nameInT9, searchQuery) ||
                        search(contact[i].phone_no, searchQuery)) {
                        count++;

                        if (count < 10) {
                            resultIndex[resSize] = i;
                            resSize++;
                        }
                    }
                }
                if (count == 0 || count > 10) {
                    printf("Total: %d\n", count);
                } else {
                    for (int i = 0; i < resSize; ++i) {
                        printf("%s %s\n", contact[resultIndex[i]].phone_no,
                               contact[resultIndex[i]].name);
                    }
                    printf("Total: %d\n", count);
                }

            } else {
                printf("Invalid not a number.\n");
            }
        } else {
            printf("Invalid operator.\n");
        }
    }



    // free resources

    for (int i = 0; i < size; ++i) {
        free(contact[i].name);
        free(contact[i].nameInT9);
    }
    free(contact);
    free(buffer);
    return EXIT_SUCCESS;
}
