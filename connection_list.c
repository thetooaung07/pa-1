//
// Created by aungthet on 1/19/24.
//


// Connection list I

#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "stdbool.h"

typedef struct TItem {
    struct TItem *m_Next;
    char m_Digit;
} TITEM;

TITEM *createItem(char digit, TITEM *next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM *l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}


bool validate(TITEM *arr) {
    // at least one digit
    if (!arr) return false;
    if (arr->m_Digit == '0' && arr->m_Next == NULL) return true;

    // does not contain extra zeros in the end

    // contains only from 0 to 9
    while (arr) {
        if (arr->m_Digit == '0' && arr->m_Next != NULL)return false;
        if (arr->m_Digit < 48 || arr->m_Digit > 57) {
            return false;
        }
        arr = arr->m_Next;
    }

    return true;
}


#endif /* __PROGTEST__ */

TITEM *addList(TITEM *a, TITEM *b) {
    if (a == NULL || b == NULL || !validate(a) || !validate(b)) {
        return NULL;
    }

    TITEM *result = NULL, *tail = NULL;
    int carry = 0;

    while (a || b || carry) {
        int sum = carry;

        if (a) {
            sum += a->m_Digit - '0';
            a = a->m_Next;
        }

        if (b) {
            sum += b->m_Digit - '0';
            b = b->m_Next;
        }

        carry = sum / 10;
        sum %= 10;


        // tricky part here
        TITEM *newNode = createItem(sum + '0', NULL);

        if (!result) {
            result = newNode;
        } else {
            tail->m_Next = newNode;
        }
        tail = newNode;
    }

    return result;
}


void print_list(TITEM *list) {

    while (list) {


        printf("%c -", list->m_Digit);
        if (list->m_Next == NULL) {
            printf("there is null\n");
        }
        list = list->m_Next;

    }
}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TITEM *a, *b, *res;

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    printf("assert 1\n");

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    printf("assert 2\n");


    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert(res->m_Digit == '3');
    assert(res->m_Next->m_Digit == '4');
    assert(res->m_Next->m_Next->m_Digit == '5');
    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    printf("assert 3\n");

    a = createItem('9',
                   createItem('8',
                              createItem('7',
                                         createItem('8',
                                                    createItem('8',
                                                               createItem('8',
                                                                          createItem('8', NULL)))))));
    b = createItem('9',
                   createItem('8',
                              createItem('7',
                                         createItem('8',
                                                    createItem('8',
                                                               createItem('8',
                                                                          createItem('8', NULL)))))));
    res = addList(a, b);
    print_list(res);

    printf("assert 4\n");

    return 0;
}

#endif /* __PROGTEST__ */

