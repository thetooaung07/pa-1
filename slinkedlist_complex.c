#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

typedef struct Node {
    char data;
    struct Node *next;
} Node;


// check if it is palindrome
void check_palindrome(Node *headRef) {
    Node *curr = headRef;
    int capacity = 10;
    int size = 0;

    char *arr = (char *) malloc((capacity + 1));

    if (!curr) {
        return;
    }

    if (curr->next == NULL) {
        printf("Palindrome\n");
        return;
    }


    while (curr) {
        if (size >= capacity) {
            capacity *= 2;
            arr = (char *) realloc(arr, capacity);
        }
        arr[size] = curr->data;
        size++;
        curr = curr->next;
    }


    int i = 0;
    int j = size - 1;
    int notPal = 0;
    while (i < j) {
        if (tolower(arr[i]) != tolower(arr[j])) {
            notPal = 1;
            break;
        }
        i++;
        j--;
    }
    if (notPal == 1) {
        printf("Not Palindrome.\n");
    } else printf("Palindrome.\n");
    free(arr);

}

int main() {

}