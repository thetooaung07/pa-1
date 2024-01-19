#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem {
    struct TItem *m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;

TITEM *createItem(int mul, int pow, TITEM *next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Mul = mul;
    n->m_Pow = pow;
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


int validate_order(TITEM *l) {
    int temp = l->m_Pow;
    l = l->m_Next;

    while (l) {
        if (l->m_Pow <= temp) {
            return 0;
        }
        temp = l->m_Pow;
        l = l->m_Next;
    }

    return 1;
}


TITEM *addPoly(TITEM *a, TITEM *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (!validate_order(a) || !validate_order(b)) {
        return NULL;
    }

    TITEM *item = NULL;

    while (a && b) {
        if (a->m_Mul == 0) {
            a = a->m_Next;
            continue;
        }
        if (b->m_Mul == 0) {
            b = b->m_Next;
            continue;
        }

        if (a->m_Pow == b->m_Pow) {
            item = createItem(a->m_Mul + b->m_Mul, a->m_Pow, item);
            a = a->m_Next;
            b = b->m_Next;
            continue;
        }

        if (a->m_Pow > b->m_Pow) {
            item = createItem(b->m_Mul, b->m_Pow, item);
            b = b->m_Next;
            continue;
        }

        if (b->m_Pow > a->m_Pow) {
            item = createItem(a->m_Mul, a->m_Pow, item);
            a = a->m_Next;
            continue;
        }
    }

    while (a) {
        if (a->m_Mul == 0) {
            a = a->m_Next;
            continue;
        }
        item = createItem(a->m_Mul, a->m_Pow, item);
        a = a->m_Next;
    }


    while (b) {
        if (b->m_Mul == 0) {
            b = b->m_Next;
            continue;
        }
        item = createItem(b->m_Mul, b->m_Pow, item);
        b = b->m_Next;
    }


    TITEM *current = item;


    while (current->m_Next) {
        if (current->m_Next->m_Mul == 0) {
            TITEM *to_remove = current->m_Next;
            current->m_Next = current->m_Next->m_Next;
            free(to_remove);
        } else {
            current = current->m_Next;
        }
    }


    if (item->m_Mul == 0) {
        TITEM *to_remove = item;
        item = item->m_Next;
        free(to_remove);
    }


    if (item == NULL) {
        item = (TITEM *) realloc(item, sizeof(TITEM));
        item->m_Mul = 0;
        item->m_Pow = 0;
        item->m_Next = 0;
    }

    return item;
}


void print_list(TITEM *l) {
    while (l) {
        printf("%dx^%d+", l->m_Mul, l->m_Pow);
        l = l->m_Next;
    }
    printf("\n");
}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TITEM *a, *b;
    TITEM *res;

    a = createItem(2, 1, NULL);
    b = createItem(0, 0, NULL);
    res = addPoly(a, b);
    assert(res->m_Mul == 2);
    assert(res->m_Pow == 1);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(2, 1, NULL);
    b = createItem(3, 1,
                   createItem(4, 2, createItem(2, 3, createItem(1, 0, NULL))));
    res = addPoly(a, b);
    assert(
            res == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(2, 1, NULL);
    b = createItem(3, 1, createItem(4, 1, NULL));
    res = addPoly(a, b);
    assert(res == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(3, 0, createItem(2, 1, createItem(9, 3, NULL)));
    b = createItem(0, 0, createItem(4, 2, createItem(-1, 3, NULL)));
//    print_list(a);
    res = addPoly(a, b);
    print_list(res);
    // assert  ( res == NULL ) ;
    // deleteList ( a ) ;
    // deleteList ( b ) ;
    // deleteList ( res ) ;

    a = createItem(3, 0, createItem(2, 1, createItem(5, 3, NULL)));
    b = createItem(-7, 0, createItem(-2, 1, createItem(-5, 3, NULL)));
    res = addPoly(a, b);
    assert(res->m_Mul == -4);
    assert(res->m_Pow == 0);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(3, 1, createItem(-2, 2, createItem(4, 3, NULL)));
    b = createItem(-3, 1, createItem(2, 2, createItem(-4, 3, NULL)));
    res = addPoly(a, b);
    assert(res->m_Mul == 0);
    assert(res->m_Pow == 0);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    return 0;
}

#endif /* __PROGTEST__ */
