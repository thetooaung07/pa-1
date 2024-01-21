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


void print_arr(int *arr, int arrSize) {

    printf("Arr - ");
    for (int i = 0; i < arrSize; ++i) {
        printf("%d,", arr[i]);
    }
    printf("\n");
}

void print_list(TITEM *list) {
    while (list) {
        printf("%c -", list->m_Digit);
        list = list->m_Next;
    }
    printf("\n");
}


#endif /* __PROGTEST__ */

TITEM *addList(TITEM *a, TITEM *b) {


    TITEM *result = NULL;

    int arrCapacity = 10;
    int arrIndex = 0;
    int *arr = (int *) malloc(10 * sizeof(int));

    if (a == NULL || b == NULL) return NULL;


    if (!validate(a) || !validate(b)) return NULL;


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
        sum = sum % 10;

        arr[arrIndex] = sum;
        arrIndex++;

        if (arrIndex >= arrCapacity) {
            arrCapacity *= 2;
            arr = (int *) realloc(arr, arrCapacity * sizeof(int));
        }
    }


    print_arr(arr, arrIndex);

    for (int i = arrIndex; i > 0; i--) {
        char digit = arr[i] + '0';

        result = createItem(digit, result);
    }

    free(arr);
    print_list(result);

    return result;
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

    printf("assert 1.\n");

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    printf("assert 2.\n");

    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    print_list(res);

//    assert(res->m_Digit == '3');
//    assert(res->m_Next->m_Digit == '4');
//    assert(res->m_Next->m_Next->m_Digit == '5');
//    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    printf("assert 3.\n");

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