#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>
 
typedef  struct TItem
 { 
	struct TItem * m_Next ; 
	int             m_Val ; 
} TITEM ;
 
TITEM * createItem (  int value , TITEM * next ) 
{ 
	TITEM * n =  ( TITEM * )  malloc  ( sizeof  (  * n ) ) ; 
	n -> m_Val = value ; 
	n -> m_Next = next ; 
	return n ; 
}

TITEM * insert_end (int value , TITEM * next){
    TITEM * new_node = (TITEM *) malloc(sizeof(TITEM));
    new_node -> m_Val = value;
    new_node -> m_Next = NULL;
    if(next == NULL){
        return new_node;
    }
    TITEM * current = next;
    while(current->m_Next){
        current = current->m_Next;
    }
    current->m_Next = new_node;
    return next;
}


void print_list(TITEM *l){
    while(l){
        printf("%d->",l->m_Val);
        l = l->m_Next;
    }
    printf("\n");
}
 
void deleteList ( TITEM * l ) 
{ 
	while  ( l ) 
	{ 
		TITEM * tmp = l -> m_Next ; 
		free  ( l ) ; 
		l = tmp ; 
	} 
}



 
TITEM * cloneLimit ( TITEM * a ,  int limit )  
{ 
    if(a==NULL || limit < 1){
        return NULL;
    }

    if(a->m_Next == NULL){
        return NULL;
    }

    TITEM * current = a;
    TITEM * result = NULL;
    while(current){
        result = insert_end(current->m_Val,result);
        current = current->m_Next;
    }

    current = result;
    print_list(result);
    while(current && current->m_Next){
        int check = 1;
        TITEM * pointer = current;
        while(pointer->m_Next){
            if(pointer->m_Next->m_Val==current->m_Val){
                if(check<limit){
                    check++;
                    pointer = pointer->m_Next;
                }
                else{
                    TITEM * to_remove = pointer->m_Next;
                    pointer->m_Next = pointer->m_Next->m_Next;
                    free(to_remove);
                }
            }
            else{
                pointer = pointer->m_Next;
            }
        }
        current = current->m_Next;
    }

    return result;
}






int main(){
    TITEM * a = NULL;
    TITEM * res = NULL;
    a = createItem(1,a);
    a = createItem(2,a);
    a = createItem(4,a);
    a = createItem(2,a);
    a = createItem(4,a);
    a = createItem(1,a);
    a = createItem(3,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(4,a);
    a = createItem(2,a);
    a = createItem(5,a);
    print_list(a);
    res = cloneLimit(a,2);
    print_list(res);
    deleteList(a);
    deleteList(res);

    a = NULL;
    res = NULL;
    a = createItem(5,a);
    a = createItem(2,a);
    a = createItem(1,a);
    a = createItem(3,a);
    a = createItem(2,a);
    a = createItem(1,a);
    print_list(a);
    res = cloneLimit(a,1);
    print_list(res);
    deleteList(a);
    deleteList(res);

    a = NULL;
    res = NULL;
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    print_list(a);
    res = cloneLimit(a,1);
    print_list(res);
    deleteList(a);
    deleteList(res);



    return 0;
}
