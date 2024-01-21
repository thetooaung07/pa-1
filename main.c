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

#endif /* __PROGTEST__ */

/* additional auxiliary functions */


bool check_input(TITEM *node) {
    if (node == NULL) return false;
    if (node->m_Digit < '0' || node->m_Digit > '9') return false;
}

void reverse(TITEM *a) {

}


TITEM *maxOf(TITEM **x, int nr) {

    if (x == NULL) {
        return NULL;
    }

    if (nr == 1) {
        return x[0];
    }


    for (int i = 0; i < nr; ++i) {
        TITEM *curr = x[i];
        if (curr == NULL) return NULL;
        while (curr) {
            if (curr->m_Digit < '0' || curr->m_Next > '9') {
                return NULL;
            }
            curr = curr->m_Next;
        }
    }

}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TITEM *a[5];

    a[0] = createItem('4',
                      createItem('3',
                                 createItem('2',
                                            createItem('1', NULL))));
    a[1] = createItem('2',
                      createItem('3',
                                 createItem('4',
                                            createItem('5', NULL))));
    maxOf(a, 2);
//    assert (maxOf(a, 2) == a[1]);
//    deleteList(a[0]);
//    deleteList(a[1]);

//    a[0] = createItem('0',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('1', NULL))));
//    a[1] = createItem('2',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('1', NULL))));
//    a[2] = createItem('1',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('1', NULL))));
//    a[3] = createItem('2',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('1',
//                                                       createItem('0',
//                                                                  createItem('0', NULL))))));
//    assert (maxOf(a, 4) == a[1]);
//    deleteList(a[0]);
//    deleteList(a[1]);
//    deleteList(a[2]);
//    deleteList(a[3]);
//
//    a[0] = createItem('1',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('0',
//                                                       createItem('0',
//                                                                  createItem('0', NULL))))));
//    a[1] = createItem('0',
//                      createItem('0',
//                                 createItem('1', NULL)));
//    a[2] = createItem('1',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('0',
//                                                       createItem('0',
//                                                                  createItem('9', NULL))))));
//    a[3] = createItem('0',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('0',
//                                                       createItem('0',
//                                                                  createItem('0',
//                                                                             createItem('0',
//                                                                                        createItem('0',
//                                                                                                   createItem('0',
//                                                                                                              createItem(
//                                                                                                                      '0',
//                                                                                                                      createItem(
//                                                                                                                              '0',
//                                                                                                                              createItem(
//                                                                                                                                      '0',
//                                                                                                                                      createItem(
//                                                                                                                                              '0',
//                                                                                                                                              createItem(
//                                                                                                                                                      '0',
//                                                                                                                                                      createItem(
//                                                                                                                                                              '0',
//                                                                                                                                                              NULL)))))))))))))));
//    assert (maxOf(a, 4) == a[2]);
//    deleteList(a[0]);
//    deleteList(a[1]);
//    deleteList(a[2]);
//    deleteList(a[3]);
//
//    a[0] = createItem('0',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('0',
//                                                       createItem('0',
//                                                                  createItem('0',
//                                                                             createItem('0',
//                                                                                        createItem('0',
//                                                                                                   createItem('0',
//                                                                                                              createItem(
//                                                                                                                      '0',
//                                                                                                                      createItem(
//                                                                                                                              '0',
//                                                                                                                              createItem(
//                                                                                                                                      '0',
//                                                                                                                                      createItem(
//                                                                                                                                              '0',
//                                                                                                                                              createItem(
//                                                                                                                                                      '0',
//                                                                                                                                                      createItem(
//                                                                                                                                                              '0',
//                                                                                                                                                              createItem(
//                                                                                                                                                                      '0',
//                                                                                                                                                                      createItem(
//                                                                                                                                                                              '0',
//                                                                                                                                                                              createItem(
//                                                                                                                                                                                      '0',
//                                                                                                                                                                                      createItem(
//                                                                                                                                                                                              '0',
//                                                                                                                                                                                              createItem(
//                                                                                                                                                                                                      '0',
//                                                                                                                                                                                                      createItem(
//                                                                                                                                                                                                              '0',
//                                                                                                                                                                                                              createItem(
//                                                                                                                                                                                                                      '1',
//                                                                                                                                                                                                                      NULL))))))))))))))))))))));
//    a[1] = createItem('1',
//                      createItem('0',
//                                 createItem('0',
//                                            createItem('0',
//                                                       createItem('0',
//                                                                  createItem('0',
//                                                                             createItem('0',
//                                                                                        createItem('0',
//                                                                                                   createItem('0',
//                                                                                                              createItem(
//                                                                                                                      '0',
//                                                                                                                      createItem(
//                                                                                                                              '0',
//                                                                                                                              createItem(
//                                                                                                                                      '0',
//                                                                                                                                      createItem(
//                                                                                                                                              '0',
//                                                                                                                                              createItem(
//                                                                                                                                                      '0',
//                                                                                                                                                      createItem(
//                                                                                                                                                              '0',
//                                                                                                                                                              createItem(
//                                                                                                                                                                      '0',
//                                                                                                                                                                      createItem(
//                                                                                                                                                                              '0',
//                                                                                                                                                                              createItem(
//                                                                                                                                                                                      '0',
//                                                                                                                                                                                      createItem(
//                                                                                                                                                                                              '0',
//                                                                                                                                                                                              createItem(
//                                                                                                                                                                                                      '0',
//                                                                                                                                                                                                      createItem(
//                                                                                                                                                                                                              '0',
//                                                                                                                                                                                                              createItem(
//                                                                                                                                                                                                                      '1',
//                                                                                                                                                                                                                      NULL))))))))))))))))))))));
//    assert (maxOf(a, 2) == a[1]);
//    deleteList(a[0]);
//    deleteList(a[1]);
//
//    a[0] = createItem('3',
//                      createItem('2',
//                                 createItem('1', NULL)));
//    a[1] = createItem('6',
//                      createItem('5',
//                                 createItem('4', NULL)));
//    a[2] = createItem('9',
//                      createItem(' c',
//                                 createItem('b',
//                                            createItem('9',
//                                                       createItem('9', NULL)))));
//    assert (maxOf(a, 3) == NULL);
//    assert (maxOf(a, 3) == NULL);
//    deleteList(a[0]);
//    deleteList(a[1]);
//    deleteList(a[2]);

    return 0;
}

#endif /* __PROGTEST__ */