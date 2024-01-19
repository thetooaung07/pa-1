#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

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


void print_list(TITEM *a) {
    while (a) {
        printf("%c", a->m_Digit);
        a = a->m_Next;
    }
    printf("\n");
}

int check(TITEM *a) {
    if (a->m_Next == NULL && a->m_Digit == '0') {
        return 1;
    }
    int zero = 0;
    while (a) {
        if (a->m_Digit < 48 || a->m_Digit > 57) {
            return 0;
        }
        if (a->m_Digit == 48) {
            zero = 1;
        } else {
            zero = 0;
        }
        a = a->m_Next;
    }
    if (zero == 1) {
        return 0;
    }
    return 1;
}

TITEM *reverse(TITEM *a) {
    TITEM *current = a;
    TITEM *previous = NULL;

    while (current) {
        TITEM *next = current->m_Next;
        current->m_Next = previous;
        previous = current;
        current = next;
    }
    return previous;
}

TITEM *addList(TITEM *a, TITEM *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (!check(a) || !check(b)) {
        return NULL;
    }


    char temp = '0', add;
    TITEM *result = NULL;
    while (a && b) {
        temp = a->m_Digit + b->m_Digit + temp - '0' - '0';
        if (temp > 57) {
            add = temp - 10;
            temp = '1';
        } else {
            add = temp;
            temp = '0';
        }
        result = createItem(add, result);
        a = a->m_Next;
        b = b->m_Next;
    }
    while (a) {
        temp = a->m_Digit + temp - '0';
        if (temp > 57) {
            add = temp - 10;
            temp = '1';
        } else {
            add = temp;
            temp = '0';
        }
        result = createItem(add, result);
        a = a->m_Next;
    }
    while (b) {
        temp = b->m_Digit + temp - '0';
        if (temp > 57) {
            add = temp - 10;
            temp = '1';
        } else {
            add = temp;
            temp = '0';
        }
        result = createItem(add, result);
        b = b->m_Next;
    }

    if (temp != '0') {
        result = createItem(temp, result);
    }

    return reverse(result);
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

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('0', NULL);
    print_list(a);
    res = addList(a, b);
    print_list(res);
    assert(res->m_Digit == '3');
    assert(res->m_Next->m_Digit == '4');
    assert(res->m_Next->m_Next->m_Digit == '5');
    assert(res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

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
    deleteList(res);
    deleteList(a);
    deleteList(b);
    return 0;
}

#endif /* __PROGTEST__ */