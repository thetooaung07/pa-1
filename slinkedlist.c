#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// check if it is palindrome
void check_palindrome(Node *headRef) {
    Node *curr = headRef;
    int capacity = 10;
    int size = 0;

    char *arr = (char *) malloc((capacity + 1));


    while (curr) {
        if (size >= capacity) {
            capacity *= 2;
            arr = (char *) realloc(arr, capacity);
        }
        arr[size] = curr->data;
        size++;
        curr = curr->next;
    }


    for (int i = 0; i < size; ++i) {

    }


}


// remove duplicates from the sorted linked list
void remove_duplicates(Node *head) {
    Node *curr = head;
    Node *next;
    if (curr == NULL) {
        return;
    }

    while (curr->next != NULL) {
        if (curr->data == curr->next->data) {
            next = curr->next->next;
            free(curr->next);
            curr->next = next;
        } else {
            curr = curr->next;
        }
    }
}


void delete_from_the_head(Node **head) {
    Node *temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// delete the node with this value
void delete_from_certain_position(Node **head, int value) {
    Node *tempNode = *head;
    Node *prev = NULL;

    if (tempNode != NULL && tempNode->data == value) {
        *head = tempNode->next;
        free(tempNode);
        return;
    }

    while (tempNode != NULL && tempNode->data != value) {
        prev = tempNode;
        tempNode = tempNode->next;
    }

    if (tempNode == NULL) {
        return;
    }

    prev->next = tempNode->next;
    free(tempNode);
}

void delete_from_the_tail(Node **head) {
    if (*head == NULL) { return; }
    if ((*head)->next == NULL) {
        free(*head);
        return;
    }
    Node *secondLast = *head;
    while (secondLast->next->next) {
        secondLast = secondLast->next;
    }
    free(secondLast->next);
    secondLast->next = NULL;
}

void insert_in_somewhere(Node *prevNode, int value) {
    // check if given node exists or not -> exit
    if (!prevNode) { return; }

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

void insert_at_the_tail(Node **headRef, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    Node *current = *headRef;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void insert_at_the_head(Node **headRef, int value) {
    // allocate new node + add data
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;

    // update new node.next to current head
    newNode->next = *headRef;

    // update new headRef
    *headRef = newNode;
}

int main() {

}