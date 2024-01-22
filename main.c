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


TITEM *createList(const char *x) {
    int i = 0;
    TITEM *item = NULL;
    while (x[i]) {
        item = createItem(x[i], item);
        x++;
    }

    return item;

}

void delList(TITEM *l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}

#endif /* __PROGTEST__ */

/* additional auxiliary functions */


void print_list(TITEM *a) {

    printf("Print - \n");


    while (a) {
        printf("%c -> ", a->m_Digit);
        a = a->m_Next;
    }

    printf("\n");
}

TITEM *reverse(TITEM *a) {
    TITEM *curr = a;
    TITEM *prev = NULL;
    while (curr) {
        TITEM *next = curr->m_Next;
        curr->m_Next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

TITEM *larger(TITEM *a, TITEM *b) {


    TITEM *aa = a;
    TITEM *bb = b;
    while (aa && bb) {
        aa = aa->m_Next;
        bb = bb->m_Next;
    }

    if (aa) return a;
    if (bb) return b;

    a = reverse(a);
    printf("a reverse  - ");
    print_list(a);
    b = reverse(b);
    printf("b reverse  - ");
    print_list(a);
    aa = a;
    bb = b;
    while (aa && bb) {
        if (bb->m_Digit > aa->m_Digit) {
            return reverse(b);
        }
        aa = aa->m_Next;
        bb = bb->m_Next;
    }

    return reverse(a);
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
            if (curr->m_Digit < '0' || curr->m_Digit > '9') {
                return NULL;
            }
            curr = curr->m_Next;
        }
    }

    TITEM *max = x[0];
    for (int i = 1; i < nr; ++i) {
        max = larger(max, x[i]);
    }


    return max;

}


#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TITEM *a[5];
    TITEM *res;

    //----- Basic test ------------------------------------------ -----
    a[0] = createList("191");
    // print_list(a[0]);
    a[1] = createList("113");
    a[2] = createList("197");
    res = maxOf(a, 3);
    print_list(res);
    print_list(a[2]);

    assert (res == a[2]);
    for (int i = 0; i < 3; i++) delList(a[i]);

    //----- Ordinal higher number ---------------------------------------- -
    a[0] = createList("313");
    a[1] = createList("1191");
    a[2] = createList("997");
    res = maxOf(a, 3);
    print_list(res);
    assert (res == a[1]);
    for (int i = 0; i < 3; i++) delList(a[i]);

    //----- Bad input ------------------------------------------ ------
//    a[0] = createList("222");
//    a[1] = NULL;
//    a[2] = createList("4333");
//    a[3] = createList("1");
//    res = maxOf(a, 4);
//
//    assert (res == NULL);
//
//    for (int i = 0; i < 4; i++) delList(a[i]);
//
//    //----- Bad value ----------------------------------------- ----
//    a[0] = createList("29a");
//    a[1] = createList("11");
//    res = maxOf(a, 2);
//
//    assert (res == NULL);
//
//    for (int i = 0; i < 2; i++) delList(a[i]);
//
//    //----- Same number ----------------------------------------- ------
//    a[0] = createList("27986");
//    a[1] = createList("3256");
//    a[2] = createList("27986");
//    a[3] = createList("17000");
//    res = maxOf(a, 4);
//
//    assert (res == a[0]);
//
//    for (int i = 0; i < 4; i++) delList(a[i]);
//
//    //----- Zero ---------------------------------------------------- -------------
//    a[0] = createList("0");
//    a[1] = createList("0");
//    a[2] = createList("0");
//    a[3] = createList("0");
//    a[4] = createList("0");
//    res = maxOf(a, 5);
//
//    assert (res == a[0]);
//
//    for (int i = 0; i < 5; i++) delList(a[i]);
//
//    //----- Unsigned Long Long Int ------------------------------------
//    a[0] = createList("0");
//    a[1] = createList("18446744073709551615");
//    a[2] = createList("1112367822345622");
//    a[3] = createList("9991234530632948235");
//    a[4] = createList("1213004921032");
//    res = maxOf(a, 5);
//    print_list(res);
//
//    assert (res == a[1]);
//
//    for (int i = 0; i < 5; i++) delList(a[i]);
//
//    //----- More like Unsigned Long Long Int ----------------------------
//    a[0] = createList("50230529401950984100481491404914091408580");
//    a[1] = createList("50230529401950123123123234492492042044242");
//    a[2] = createList("50230529401950984100480123032931110119944");
//    a[3] = createList("50230529401950123123123234492400000000000");
//    a[4] = createList("50230531000000000000000000000000000000000");
//    res = maxOf(a, 5);
//
//    assert (res == a[4]);
//
//    for (int i = 0; i < 5; i++) delList(a[i]);
//
//    //----- Greater than Unsigned Long Long Int different long --------------
//    a[0] = createList("253051330239013091349049023023");
//    a[1] = createList("253051330239013091349049023024");
//    a[2] = createList("2094241212100000000000100100");
//    a[3] = createList("999919103904248923023");
//    a[4] = createList("9999999999999999999999999999");
//    res = maxOf(a, 5);
//
//    assert (res == a[1]);
//
//    for (int i = 0; i < 5; i++) delList(a[i]);
    return 0;
}

#endif /* __PROGTEST__ */