#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem *m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;

TITEM *createItem(int mul, int pow, TITEM *next)
{
    TITEM *n = (TITEM *)malloc(sizeof(*n));
    n->m_Mul = mul;
    n->m_Pow = pow;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM *l)
{
    while (l)
    {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

void print_list(TITEM *l)
{
    while (l)
    {
        printf("%dx^%d+", l->m_Mul, l->m_Pow);
        l = l->m_Next;
    }
    printf("\n");
}

int order(TITEM *l)
{
    int temp = l->m_Pow;
    l = l->m_Next;
    while (l)
    {
        if (l->m_Pow <= temp)
        {
            return 0;
        }
        temp = l->m_Pow;
        l = l->m_Next;
    }

    return 1;
}

TITEM *addPoly(TITEM *a, TITEM *b)
{
    if (a == NULL || b == NULL)
    {
        return NULL;
    }

    if (!order(a) || !order(b))
    {
        return NULL;
    }

    printf("not edged case\n");
    TITEM *result = NULL;
    while (a && b)
    {
        if (a->m_Mul == 0)
        {
            a = a->m_Next;
            continue;
        }
        if (b->m_Mul == 0)
        {
            b = b->m_Next;
            continue;
        }
        if (a->m_Pow == b->m_Pow)
        {
            result = createItem(a->m_Mul + b->m_Mul, a->m_Pow, result);
            a = a->m_Next;
            b = b->m_Next;
            continue;
        }
        if (a->m_Pow < b->m_Pow)
        {
            result = createItem(a->m_Mul, a->m_Pow, result);
            a = a->m_Next;
            continue;
        }
        if (b->m_Pow < a->m_Pow)
        {
            result = createItem(b->m_Mul, b->m_Pow, result);
            b = b->m_Next;
            continue;
        }
    }

    while (a)
    {
        if (a->m_Mul == 0)
        {
            a = a->m_Next;
            continue;
        }
        result = createItem(a->m_Mul, a->m_Pow, result);
        a = a->m_Next;
    }

    while (b)
    {
        if (a->m_Mul == 0)
        {
            a = a->m_Next;
            continue;
        }
        result = createItem(b->m_Mul, b->m_Pow, result);
        b = b->m_Next;
    }

    TITEM *current = result;
    while (current->m_Next)
    {
        if (current->m_Next->m_Mul == 0)
        {
            TITEM *to_remove = current->m_Next;
            current->m_Next = current->m_Next->m_Next;
            free(to_remove);
        }
        else
        {
            current = current->m_Next;
        }
    }
    if (result->m_Mul == 0)
    {
        TITEM *to_remove = result;
        result = result->m_Next;
        free(to_remove);
    }

    if (result == NULL)
    {
        result = (TITEM *)realloc(result, sizeof(TITEM));
        result->m_Mul = 0;
        result->m_Pow = 0;
        result->m_Next = 0;
    }

    return result;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    TITEM *a, *b;
    TITEM *res;

    a = createItem(2, 1, NULL);
    b = createItem(0, 0, NULL);
    res = addPoly(a, b);
    print_list(res);
    assert(res->m_Mul == 2);
    assert(res->m_Pow == 1);
    assert(res->m_Next == NULL);
    deleteList(a);
    deleteList(b);
    deleteList(res);

    a = createItem(2, 1, NULL);
    b = createItem(3, 1, createItem(4, 2, createItem(2, 3, createItem(1, 0, NULL))));
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
    print_list(a);
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
