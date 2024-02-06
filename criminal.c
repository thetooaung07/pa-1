//
// Created by aungthet on 2/5/24.
//
#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCriminal {
    struct TCriminal *m_Next;
    char *m_Name;
    struct TCriminal **m_Contacts;
    size_t m_Cnt;
    size_t m_Capacity;
} TCRIMINAL;

#endif /* __PROGTEST__ */

void print_list(TCRIMINAL *l) {

    printf("\nPrint List\n");
    TCRIMINAL *curr = l;
    printf("contact count %d\n", curr->m_Cnt);

    while (curr) {
        printf("%s->", curr->m_Name);
        curr = curr->m_Next;
    }
    printf("\n");

    curr = l;
    for (int i = 0; i < curr->m_Cnt; ++i) {
        printf("%s=>", curr->m_Contacts[i]->m_Name);
    }
    printf("\n");
    printf("\n");

}


TCRIMINAL *createRecord(const char *name,
                        TCRIMINAL *next) {
    /* todo */

    TCRIMINAL *newCr = (TCRIMINAL *) malloc(sizeof(TCRIMINAL));
    newCr->m_Next = next;
    newCr->m_Name = (char *) malloc((strlen(name)) * sizeof(char));
    strcpy(newCr->m_Name, name);
    newCr->m_Cnt = 0;
    newCr->m_Contacts = NULL;
    newCr->m_Capacity = 0;
    return newCr;
}


void addContact(TCRIMINAL *dst,
                TCRIMINAL *contact) {


    dst->m_Cnt += 1;

    if (dst->m_Cnt > dst->m_Capacity) {
        if (dst->m_Capacity == 0) dst->m_Capacity = 1;
        else dst->m_Capacity *= 2;
        dst->m_Contacts = (TCRIMINAL **) realloc(dst->m_Contacts,
                                                 dst->m_Capacity *
                                                 sizeof(TCRIMINAL *));
    }
    dst->m_Contacts[dst->m_Cnt - 1] = contact;

}


TCRIMINAL *cloneList(TCRIMINAL *src) {

    if (src == NULL) { return NULL; }
    TCRIMINAL *newHead = NULL;
    TCRIMINAL *original = src;
    TCRIMINAL *newPrev = NULL;


    while (original != NULL) {
        TCRIMINAL *newNode = createRecord(original->m_Name, NULL);

        if (newHead == NULL) {
            newHead = newNode;
        } else {
            newPrev->m_Next = newNode;
        }
        newPrev = newNode;


        for (int i = 0; i < original->m_Cnt; ++i) {
            TCRIMINAL *originalContact = original->m_Contacts[i];
            TCRIMINAL *newContact = NULL;
            TCRIMINAL *temp = newHead;

            while (temp != NULL) {
                if (strcmp(temp->m_Name, originalContact->m_Name)) {
                    newContact = temp;
                    break;

                }
                temp = temp->m_Next;

            }


            if (newContact == NULL) {
                newContact = createRecord(newContact->m_Name, NULL);
                newContact->m_Cnt = 0;
                addContact(newPrev, newContact);
            }

            addContact(newPrev, newContact);
        }

        original = original->m_Next;
    }

    return newHead;
}


TCRIMINAL *clone_List(TCRIMINAL *src) {
    if (!src) return NULL;  // Return NULL if source list is empty

    TCRIMINAL *newHead = NULL;  // Initialize the head of the new list
    TCRIMINAL *srcCurr = src;   // Pointer to traverse the source list
    TCRIMINAL *newPrev = NULL;  // Pointer to track the previous node in the new list





    // Traverse the source list and create a deep copy of each node
    while (srcCurr != NULL) {
        // Create a new node
        TCRIMINAL *newNode = createRecord(srcCurr->m_Name, NULL);

        // Add the new node to the new list
        if (!newHead) {
            newHead = newNode;  // Set the head of the new list
        } else {
            newPrev->m_Next = newNode;  // Link the previous node to the new node
        }

        // Update the previous node in the new list
        newPrev = newNode;

        // Update the contacts for the new node
        for (size_t i = 0; i < srcCurr->m_Cnt; ++i) {
            TCRIMINAL *srcContact = srcCurr->m_Contacts[i];
            TCRIMINAL *newContact = NULL;
            TCRIMINAL *tmp = newHead;

            // Find the corresponding contact in the new list
            while (tmp != NULL) {
                if (strcmp(tmp->m_Name, srcContact->m_Name) == 0) {
                    newContact = tmp;
                    break;
                }
                tmp = tmp->m_Next;
            }

            // If contact not found, create a new node and add it to the new list
            if (!newContact) {
                newContact = createRecord(srcContact->m_Name, NULL);
                newContact->m_Cnt = 0;  // Reset contact count
                addContact(newPrev, newContact);  // Add contact to the new node
            }

            // Add the contact to the new node's contacts
            addContact(newNode, newContact);
        }

        // Move to the next node in the source list
        srcCurr = srcCurr->m_Next;
    }

    return newHead;  // Return the head of the new list
}


void freeList(TCRIMINAL *src) {
    /* todo */
}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TCRIMINAL *a, *b;
    char tmp[100];

    assert(sizeof(TCRIMINAL) == 3 * sizeof(void *) + 2 * sizeof(size_t));
    a = NULL;
    a = createRecord("Peter", a);
    a = createRecord("John", a);
    a = createRecord("Joe", a);
    a = createRecord("Maria", a);


    addContact(a, a->m_Next);
    addContact(a->m_Next->m_Next, a->m_Next->m_Next->m_Next);
    addContact(a->m_Next->m_Next->m_Next, a->m_Next);


    assert(a
           && !strcmp(a->m_Name, "Maria")
           && a->m_Cnt == 1
           && a->m_Contacts[0] == a->m_Next);
    assert(a->m_Next
           && !strcmp(a->m_Next->m_Name, "Joe")
           && a->m_Next->m_Cnt == 0);
    assert(a->m_Next->m_Next
           && !strcmp(a->m_Next->m_Next->m_Name, "John")
           && a->m_Next->m_Next->m_Cnt == 1
           && a->m_Next->m_Next->m_Contacts[0] == a->m_Next->m_Next->m_Next);
    assert(a->m_Next->m_Next->m_Next
           && !strcmp(a->m_Next->m_Next->m_Next->m_Name, "Peter")
           && a->m_Next->m_Next->m_Next->m_Cnt == 1
           && a->m_Next->m_Next->m_Next->m_Contacts[0] == a->m_Next);
    assert(a->m_Next->m_Next->m_Next->m_Next == NULL);


    b = cloneList(a);



//    strcpy(tmp, "Moe");
//    a = createRecord(tmp, a);
//    strcpy(tmp, "Victoria");
//    a = createRecord(tmp, a);
//    strcpy(tmp, "Peter");
//    a = createRecord(tmp, a);
//    addContact(b->m_Next->m_Next->m_Next, b->m_Next->m_Next);
//    assert(a
//           && !strcmp(a->m_Name, "Peter")
//           && a->m_Cnt == 0);
//    assert(a->m_Next
//           && !strcmp(a->m_Next->m_Name, "Victoria")
//           && a->m_Next->m_Cnt == 0);
//    assert(a->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Name, "Moe")
//           && a->m_Next->m_Next->m_Cnt == 0);
//    assert(a->m_Next->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Next->m_Name, "Maria")
//           && a->m_Next->m_Next->m_Next->m_Cnt == 1
//           && a->m_Next->m_Next->m_Next->m_Contacts[0] == a->m_Next->m_Next->m_Next->m_Next);
//    assert(a->m_Next->m_Next->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Next->m_Next->m_Name, "Joe")
//           && a->m_Next->m_Next->m_Next->m_Next->m_Cnt == 0);
//    assert(a->m_Next->m_Next->m_Next->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "John")
//           && a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Cnt == 1
//           && a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Contacts[0] ==
//              a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next);
//    assert(a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Peter")
//           && a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Cnt == 1
//           && a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Contacts[0] == a->m_Next->m_Next->m_Next->m_Next);
//    assert(a->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == nullptr);
//    assert(b
//           && !strcmp(b->m_Name, "Maria")
//           && b->m_Cnt == 1
//           && b->m_Contacts[0] == b->m_Next);
//    assert(b->m_Next
//           && !strcmp(b->m_Next->m_Name, "Joe")
//           && b->m_Next->m_Cnt == 0);
//    assert(b->m_Next->m_Next
//           && !strcmp(b->m_Next->m_Next->m_Name, "John")
//           && b->m_Next->m_Next->m_Cnt == 1
//           && b->m_Next->m_Next->m_Contacts[0] == b->m_Next->m_Next->m_Next);
//    assert(b->m_Next->m_Next->m_Next
//           && !strcmp(b->m_Next->m_Next->m_Next->m_Name, "Peter")
//           && b->m_Next->m_Next->m_Next->m_Cnt == 2
//           && b->m_Next->m_Next->m_Next->m_Contacts[0] == b->m_Next
//           && b->m_Next->m_Next->m_Next->m_Contacts[1] == b->m_Next->m_Next);
//    assert(b->m_Next->m_Next->m_Next->m_Next == nullptr);
//    freeList(a);
//    addContact(b->m_Next, b->m_Next);
//    a = cloneList(b);
//    assert(a
//           && !strcmp(a->m_Name, "Maria")
//           && a->m_Cnt == 1
//           && a->m_Contacts[0] == a->m_Next);
//    assert(a->m_Next
//           && !strcmp(a->m_Next->m_Name, "Joe")
//           && a->m_Next->m_Cnt == 1
//           && a->m_Next->m_Contacts[0] == a->m_Next);
//    assert(a->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Name, "John")
//           && a->m_Next->m_Next->m_Cnt == 1
//           && a->m_Next->m_Next->m_Contacts[0] == a->m_Next->m_Next->m_Next);
//    assert(a->m_Next->m_Next->m_Next
//           && !strcmp(a->m_Next->m_Next->m_Next->m_Name, "Peter")
//           && a->m_Next->m_Next->m_Next->m_Cnt == 2
//           && a->m_Next->m_Next->m_Next->m_Contacts[0] == a->m_Next
//           && a->m_Next->m_Next->m_Next->m_Contacts[1] == a->m_Next->m_Next);
//    assert(a->m_Next->m_Next->m_Next->m_Next == nullptr);
//    assert(b
//           && !strcmp(b->m_Name, "Maria")
//           && b->m_Cnt == 1
//           && b->m_Contacts[0] == b->m_Next);
//    assert(b->m_Next
//           && !strcmp(b->m_Next->m_Name, "Joe")
//           && b->m_Next->m_Cnt == 1
//           && b->m_Next->m_Contacts[0] == b->m_Next);
//    assert(b->m_Next->m_Next
//           && !strcmp(b->m_Next->m_Next->m_Name, "John")
//           && b->m_Next->m_Next->m_Cnt == 1
//           && b->m_Next->m_Next->m_Contacts[0] == b->m_Next->m_Next->m_Next);
//    assert(b->m_Next->m_Next->m_Next
//           && !strcmp(b->m_Next->m_Next->m_Next->m_Name, "Peter")
//           && b->m_Next->m_Next->m_Next->m_Cnt == 2
//           && b->m_Next->m_Next->m_Next->m_Contacts[0] == b->m_Next
//           && b->m_Next->m_Next->m_Next->m_Contacts[1] == b->m_Next->m_Next);
//    assert(b->m_Next->m_Next->m_Next->m_Next == nullptr);
//    freeList(b);
//    freeList(a);
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */