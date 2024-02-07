//
// Created by Thet Oo Aung on 03/02/2024.
//
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"


typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;


void reverse_dd(Node **head) {
    Node *temp;
    Node *curr = *head;

    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp != NULL) {
        *head = temp->prev;
    }
}

void insert_after_target_node() {}


void insert_front(Node **head, int value) {

    Node *newNode = (Node *) malloc(sizeof(Node));
    Node *curr = *head;


    newNode->data = value;
    newNode->next = curr;
    newNode->prev = NULL;

    if (curr) {
        curr->prev = newNode;
    }

    *head = newNode;
}

void insert_last(Node **head, int value) {
    Node *newNode = (Node *) malloc((sizeof(Node)));
    Node *curr = *head;

    newNode->next = NULL;
    newNode->data = value;

    if ((*head) == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    while (curr && curr->next) {
        curr = curr->next;
    }


    curr->next = newNode;
    newNode->prev = curr;


}

void delete_from_head(Node **head) {
    if (*head == NULL) { return; }

    Node *temp = *head;

    if (temp->next != NULL) {
        temp->next->prev = NULL;
    }

    *head = temp->next;

    free(temp);

}

void delete_last_node(Node **head) {
    Node *temp = *head;
    if (!temp) { return; }
    if (temp->next == NULL) {
        free(temp);
        return;
    }

    while (temp->next) {
        temp = temp->next;
    }

    temp->prev = NULL;
    free(temp);

}

void delete_target(Node **head, int key) {

    if (*head == NULL || !isdigit(key)) {
        return;
    }
    Node *curr = *head;
    while (curr && curr->data != key) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return;
    }
    if (*head == curr) {
        *head = curr->next;
    }

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    }
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }
    free(curr);

}

void print_list(Node *head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void test_insert_front(Node **head, int value) {
    insert_front(head, value);
    printf("Inserted %d at front: ", value);
    print_list(*head);
}

int main() {
    Node *head = NULL;

    // Test with an empty list
    test_insert_front(&head,
                      5);  // Expected output: Inserted 5 at front: List: 5

    // Test with a list containing one node
    test_insert_front(&head,
                      10);  // Expected output: Inserted 10 at front: List: 10 5

    // Test with a list containing multiple nodes
    test_insert_front(&head,
                      15);  // Expected output: Inserted 15 at front: List: 15 10 5

    // Test with negative value
    test_insert_front(&head,
                      -20); // Expected output: Inserted -20 at front: List: -20 15 10 5

    // Test with zero value
    test_insert_front(&head,
                      0); // Expected output: Inserted 0 at front: List: 0 -20 15 10 5

    // Test with large value
    test_insert_front(&head,
                      1000); // Expected output: Inserted 1000 at front: List: 1000 0 -20 15 10 5

    // Test with repeating value
    test_insert_front(&head,
                      15); // Expected output: Inserted 15 at front: List: 15 1000 0 -20 15 10 5


    return EXIT_SUCCESS;
}