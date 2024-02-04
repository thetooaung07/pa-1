#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void swapNodes(Node **headRef, int x, int y) {
    if (x == y) { return; }

    // x and y are adjacent to each other
//     - one of x or y is head node or tail node
//     - none of x and y is either a head node or tail

    // x and y are far apart
//       - one of x and y are head or tail
//       - not head or tail

    // x and y values does not present in list

    Node *prevX = NULL, *currX = *headRef;
    while (currX && currX->data != x) {
        prevX = currX;
        currX = currX->next;
    }

    Node *prevY = NULL, *currY = *headRef;
    while (currY && currY->data != x) {
        prevY = currY;
        currY = currY->next;
    }

    if (currX == NULL || currY == NULL) {
        return;
    }

    if (prevX != NULL) { prevX->next = currY; }
    else *headRef = currY;

    if (prevY != NULL) { prevY->next = currX; }
    else *headRef = currX;

    Node *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

void reverse(Node **head) {
    Node *prev = NULL;
    Node *curr = *head;
    Node *next = NULL;

    if (!curr || !curr->next) {
        return;
    }

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void remove_duplicate_from_unsorted_list(Node *head) {
    Node *ptr1, *ptr2, *dup;
    ptr1 = head;

    if (ptr1 == NULL || ptr1->next == NULL) {
        return;
    }
    while (ptr1 && ptr1->next) {
        ptr2 = ptr1;

        while (ptr2->next) {
            if (ptr2->next->data == ptr1->data) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            } else {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
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