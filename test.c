#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//structure for storing phone number, name and the name in T9 format (all as strings)
typedef struct contact {
    char *phoneNum;
    char *name;
    char *nameInT9;
} Contact;

//takes in a character and returns a corresponding number in T9 as character
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

char *stringToT9(char *string) {
    int length = strlen(string);
    char *T9String = (char *) malloc(length + 1);

    for (int i = 0; i < length; i++) {
        T9String[i] = charToT9(tolower(string[i]));
    }

    T9String[length] = '\0';
    return T9String;
}

int isPrefix(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

Contact *pushArray(Contact *array, size_t *size, size_t *capacity,
                   char *phoneNum, char *name) {

    if (*size >= *capacity) {
        if (*capacity == 0) (*capacity)++;
        else *capacity *= 2;
        array = (Contact *) realloc(array, (*capacity) * sizeof(*array));
    }

    array[*size].phoneNum = (char *) malloc(strlen(phoneNum) + 1);
    strcpy(array[*size].phoneNum, phoneNum);
    array[*size].name = (char *) malloc(strlen(name) + 1);
    strcpy(array[*size].name, name);
    array[*size].nameInT9 = stringToT9(name);
    (*size)++;
    return array;
}

void removeNL(char *string) {
    int length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }
}

int isNumber(char *s) {
    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}

int checkIfValidPlusFormat(char *string) {
    int i = 2;
    int countDigit = -1;
    int stringLen = strlen(string);
    if (string[1] != ' ' || !(isdigit(string[2]))) {
        return 0;
    } else {
        int phoneStart = 1;

        while (phoneStart) {
            if (!isdigit(string[i])) phoneStart = 0;
            i++;
            countDigit++;
        }
    }

    if (countDigit > 20) return 0;

    if (string[i - 1] != ' ' || !isalpha(string[i])) {
        return 0;
    } else {
        while (i < stringLen) {
            if (string[i] != ' ' && !isalpha(string[i])) {
                return 0;
            }
            if (i == stringLen - 1) {
                if (string[i] == ' ') return 0;
            }
            i++;
        }
    }

    return 1;
}

int main() {
    char *input = NULL;
    size_t stringLen = 0;
    char *phone;
    char *name;

    Contact *contacts = NULL;
    size_t size = 0;
    size_t capacity = 0;

    while (getline(&input, &stringLen, stdin) != EOF) {
        removeNL(input);
        int flag = 0;
        int countResult = 0;

        if (input[0] == '+') {
            if (checkIfValidPlusFormat(input)) {
                phone = strtok(input + 2, " ");
                name = strtok(NULL, "\0");

                for (size_t i = 0; i < size; i++) {
                    if (strcmp(phone, contacts[i].phoneNum) == 0 &&
                        strcmp(name, contacts[i].name) == 0) {
                        printf("Duplicate contact.\n");
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    contacts = pushArray(contacts, &size, &capacity, phone,
                                         name);
                    printf("OK\n");
                }
            } else {
                printf("Invalid input.\n");
            }
        } else if (input[0] == '?') {
            char *request = input + 2;
            if (*request == '\0') {
                printf("Invalid input.\n");
                continue;
            }

            if (isNumber(request)) {
                for (size_t i = 0; i < size; i++) {
                    if (isPrefix(contacts[i].nameInT9, request) ||
                        isPrefix(contacts[i].phoneNum, request)) {
                        countResult++;
                    }
                }

                if (countResult > 10 || countResult == 0) {
                    printf("Total: %d\n", countResult);
                } else {
                    for (size_t i = 0; i < size; i++) {
                        if (isPrefix(contacts[i].nameInT9, request) ||
                            isPrefix(contacts[i].phoneNum, request)) {
                            printf("%s %s\n", contacts[i].phoneNum,
                                   contacts[i].name);
                        }
                    }
                    printf("Total: %d\n", countResult);
                }
            } else {
                printf("Invalid input.\n");
            }
        } else {
            printf("Invalid input.\n");
        }
    }

    for (size_t i = 0; i < size; i++) {
        free(contacts[i].phoneNum);
        free(contacts[i].name);
        free(contacts[i].nameInT9);
    }
    free(contacts);
    free(input);
}