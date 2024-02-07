#ifndef __PROGTEST__
 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>
 
typedef  struct TItem { 
    struct TItem * m_Next ; 
    char m_Digit ; 
} TITEM ;
 
TITEM * createItem ( char digit , TITEM * next )  { 
    TITEM * n =  ( TITEM * )  malloc ( sizeof ( * n ) ) ; 
    n -> m_Digit = digit ; 
    n -> m_Next = next ; 
    return n ; 
}
 
void deleteList ( TITEM * l )  { 
    while  ( l )  { 
        TITEM * tmp = l -> m_Next ; 
        free ( l ) ; 
        l = tmp ; 
    } 
}
 
#endif /* __PROGTEST__ */

TITEM * insert_end (TITEM * next,char digit){
    TITEM * new_node = (TITEM *) malloc(sizeof(TITEM));
    new_node->m_Digit = digit;
    new_node->m_Next = NULL;
    if(next==NULL){
        return new_node;
    }
    TITEM * current = next;
    while(current->m_Next){
        current = current->m_Next;
    }
    current->m_Next = new_node;
    return next;
}
 
int valid(TITEM * a){
    if(a->m_Next==NULL && a->m_Digit=='0'){
        return 1;
    }
    TITEM * current = a;
    int zero = 1;
    while(current){
        if(current->m_Digit<48 || current->m_Digit>57){
            return 0;
        }
        if(current->m_Digit==48){
            zero = 1;
        }
        else{
            zero = 0;
        }
        current = current->m_Next;
    }
    if(zero==1){
        return 0;
    }
    return 1;
}

void print_list (TITEM * a){
    if(a==NULL){
        printf("NULL LIST\n");
        return;
    }
    while(a){
        printf("%c -> ",a->m_Digit);
        a = a->m_Next;
    }
    printf("\n");
}

TITEM * addList(TITEM * a, TITEM * b){
    if(a==NULL || b==NULL){
        return NULL;
    }
    if(!valid(a)||!valid(b)){
        return NULL;
    }

    TITEM * result = NULL;


    char temp = '0';
    while(a&&b){
        char sum = '0';
        sum = a->m_Digit + b->m_Digit + temp -'0'-'0';
        if(sum > '9'){
            sum = sum - 10;
            temp = '1';
        }
        result = insert_end(result,sum);
        a=a->m_Next;
        b=b->m_Next;
    }
    while(a){
        result = insert_end(result,a->m_Digit);
        a = a->m_Next;
    }
    while(b){
        result = insert_end(result,a->m_Digit);
        b=b->m_Next;
    }

    if(temp=='1'){
        result = insert_end(result,temp);
    }
    
    return result;

}
 
#ifndef __PROGTEST__
 
int main ( int argc ,  char  * argv [ ] )  { 
    TITEM * a ,  * b ,  * res ;
 
    a = createItem ( 'x' , NULL ) ; 
    b = createItem ( '3' , NULL ) ; 
    res = addList ( a , b ) ; 
    print_list(res);
    assert  ( res == NULL ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ;
 
    a = createItem ( '5' , 
         createItem ( '0' , 
          createItem ( '0' , NULL ) ) ) ; 
    b = createItem ( '3' , NULL ) ; 
    res = addList ( a , b ) ; 
    print_list(res);
    assert  ( res == NULL ) ; 
    deleteList ( a ) ; 
    deleteList (b ) ;
 
    a = createItem ( '3' , 
         createItem ( '4' , 
          createItem ( '5' , NULL ) ) ) ; 
    b = createItem ( '0' , NULL ) ; 
    res = addList ( a , b ) ; 
    print_list(res);
    assert  ( res -> m_Digit ==  '3' ) ; 
    assert  ( res -> m_Next-> m_Digit ==  '4' ) ; 
    assert  ( res -> m_Next -> m_Next -> m_Digit ==  '5' ) ; 
    assert  ( res -> m_Next -> m_Next -> m_Next == NULL ) ; 
    deleteList ( res ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 


     a = createItem ( '5' , 
         createItem ( '5' , 
          createItem ( '5' , NULL ) ) ) ; 
    b = createItem ( '5' , 
         createItem ( '5' , 
          createItem ( '5' , NULL ) ) ) ; 
    res = addList ( a , b ) ; 
    print_list(res);
    deleteList ( res ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 

    a = createItem ( '7' , 
         createItem ( '6' , 
          createItem ( '3' , NULL ) ) ) ; 
    b = createItem ( '3' , 
         createItem ( '3' , 
          createItem ( '6' , NULL ) ) ) ; 
    res = addList ( a , b ) ; 
    print_list(res);
    deleteList ( res ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 


    return  0 ; 
}
 
#endif /* __PROGTEST__ */



