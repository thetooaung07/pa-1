#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
    struct TItem *m_Next;
    char *m_Name;
    char m_Secret[24];
} TITEM;

int cmpName(const TITEM *a,
            const TITEM *b)
{
    return strcmp(a->m_Name, b->m_Name);
}

int cmpNameInsensitive(const TITEM *a,
                       const TITEM *b)
{
    return strcasecmp(a->m_Name, b->m_Name);
}

int cmpNameLen(const TITEM *a,
               const TITEM *b)
{
    size_t la = strlen(a->m_Name), lb = strlen(b->m_Name);
    return (lb < la) - (la < lb);
}
#endif /* __PROGTEST__ */

TITEM *newItem(const char *name,
               TITEM *next)
{
    TITEM *new_node = (TITEM *)malloc(sizeof(TITEM));
    new_node->m_Name = (char *)malloc(sizeof(strlen(name) + 2));
    strcpy(new_node->m_Name, name);
    if (next == NULL)
    {
        new_node->m_Next = NULL;
        next = new_node;
        return next;
    }
    new_node->m_Next = next;
    next = new_node;
    return next;
}
TITEM *divider(TITEM *l)
{
    TITEM * hare = l->m_Next;
    TITEM * tortoise = l;
    while(hare->m_Next){
        hare= hare->m_Next;
        if(hare->m_Next){
            hare = hare->m_Next;
            tortoise = tortoise->m_Next;
        }
    }
    return tortoise;
}

TITEM * merge(TITEM *a, TITEM * b , int ascending , int (*cmpFn)(const TITEM *, const TITEM *) ){
    int constant = 1 ;
    if(ascending==0) constant = -1;
    TITEM * sorted;
    if((constant * cmpFn(a,b))<=0){
        sorted = a;
        a = a->m_Next;
    }
    else{
        sorted = b;
        b = b->m_Next;
    }
    TITEM * head = sorted;
    while(a!=NULL && b!= NULL){
        if((constant * cmpFn(a,b))<=0){
        sorted->m_Next = a;
        a = a->m_Next;
        sorted = sorted->m_Next;
    }
    else{
        sorted->m_Next = b;
        b = b->m_Next;
        sorted = sorted->m_Next;
    }
    }
    if(a!=NULL){
        sorted->m_Next = a;
    }
    if(b!=NULL){
        sorted->m_Next = b;
    }
    return head;
}

TITEM *recursion(TITEM *l, int ascending, int (*cmpFn)(const TITEM *, const TITEM *))
{
    if (l == NULL)
    {
        return l;
    }
    if (l->m_Next == NULL)
    {
        return l;
    }

    TITEM *mid = divider(l);
    TITEM * unlinked = mid;
    mid = mid->m_Next;
    unlinked->m_Next=NULL;
    TITEM *list1 = recursion(l, ascending, cmpFn);
    TITEM *list2 = recursion(mid, ascending, cmpFn);
    l = merge(list1, list2 ,ascending , cmpFn);
    return l;
}

TITEM *sortListCmp(TITEM *l,
                   int ascending,
                   int (*cmpFn)(const TITEM *, const TITEM *))
{
    if (l == NULL)
    {
        return NULL;
    }
    if (l->m_Next == NULL)
    {
        return l;
    }

    l = recursion(l, ascending, cmpFn);
    return l;
}

TITEM * reverse_list(TITEM * l){
    if(l==NULL){
        return l;
    }
    if(l->m_Next == NULL){
        return l;
    }
    TITEM * current = l;
    TITEM * previous = NULL;
    while(current){
        TITEM * temp = current->m_Next;
        current->m_Next = previous;
        previous = current;
        current = temp;
    }
    return previous;

}

void freeList(TITEM *src)
{
    TITEM *current = src;
    while (current)
    {
        TITEM *to_free = current;
        current = current->m_Next;
        free(to_free->m_Name);
        free(to_free);
    }
}

void printList(TITEM *l)
{
    TITEM *curent = l;
    while (curent)
    {
        printf("%s -> ", curent->m_Name);
        curent = curent->m_Next;
    }
    printf("\n");
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    TITEM *l;
    char tmp[50];

    assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
    l = NULL;
    l = newItem("BI-PA1", l);
    l = newItem("BIE-PA2", l);
    l = newItem("NI-PAR", l);
    l = newItem("lin", l);
    l = newItem("AG1", l);
    printList(l);
    assert(l && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
    assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
    assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
      l = sortListCmp ( l, 1, cmpName );
      printList(l);
      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 1, cmpNameInsensitive );
      printList(l);
      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 1, cmpNameLen );
      printList(l);
      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = newItem ( "AAG.3", l );
      printList(l);
      assert ( l
               && ! strcmp ( l -> m_Name, "AAG.3" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 0, cmpNameLen );
      printList(l);

      assert ( l
               && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      freeList ( l );
      l = NULL;
      strncpy ( tmp, "BI-PA1", sizeof ( tmp ) - 1 );
      tmp[sizeof ( tmp ) - 1 ] = '\0';
      l = newItem ( tmp, l );
      strncpy ( tmp, "BIE-PA2", sizeof ( tmp ) - 1 );
      tmp[sizeof ( tmp ) - 1 ] = '\0';
      l = newItem ( tmp, l );
      strncpy ( tmp, "NI-PAR", sizeof ( tmp ) - 1 );
      tmp[sizeof ( tmp ) - 1 ] = '\0';
      l = newItem ( tmp, l );
      strncpy ( tmp, "lin", sizeof ( tmp ) - 1 );
      tmp[sizeof ( tmp ) - 1 ] = '\0';
      l = newItem ( tmp, l );
      strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
      tmp[sizeof ( tmp ) - 1 ] = '\0';
      l = newItem ( tmp, l );
      printList(l);
      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 1, cmpName );
      printList(l);

      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 1, cmpNameInsensitive );
      printList(l);

      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 1, cmpNameLen );
      printList(l);

      assert ( l
               && ! strcmp ( l -> m_Name, "AG1" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      strncpy ( tmp, "AAG.3", sizeof ( tmp ) - 1 );
      tmp[sizeof ( tmp ) - 1 ] = '\0';
      l = newItem ( tmp, l );
      printList(l);

      assert ( l
               && ! strcmp ( l -> m_Name, "AAG.3" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
      l = sortListCmp ( l, 0, cmpNameLen );
      printList(l);


      assert ( l
               && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
      assert ( l -> m_Next
               && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
      assert ( l -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
      assert ( l -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
               && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
      assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    //   freeList ( l );
    printf("Reversing....\n");
    l = reverse_list(l);
    printList(l);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
