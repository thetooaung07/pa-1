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

TITEM * reverse_list (TITEM * l){
    TITEM * previous = NULL;
    TITEM * current = l;
    while(current){
        TITEM * next = current->m_Next;
        current->m_Next = previous;
        previous = current;
        current = next;
    }
    return previous;
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

void print_list(TITEM * a){
    if(a==NULL){
        printf("NULL\n");
        return;
    }
    while(a){
        printf("%d -> " , a->m_Val );
        a = a->m_Next;
    }
    printf("\n");
}


TITEM * cloneLimit ( TITEM * a ,  int limit )  
{   
    if(a==NULL){
        return NULL;
    }
    if(limit<=0){
        return NULL;
    }


    TITEM * result = NULL;
    TITEM  * current = a;
    while(current){
        int count = 1;
        TITEM * temp = current;
        while(temp->m_Next){
            if(temp->m_Next->m_Val==current->m_Val){
                count++;
                if(count > limit){
                    TITEM * to_remove = temp->m_Next;
                    temp->m_Next = temp->m_Next->m_Next;
                    free(to_remove);
                }
                else{
                    temp = temp->m_Next;
                }
            }
            else{
                temp = temp->m_Next;
            }
        }
        result = createItem(current->m_Val,result);
        current = current->m_Next;
    }
    
    return reverse_list(result);
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

    a = NULL;
    res = NULL;
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    a = createItem(1,a);
    print_list(a);
    res = cloneLimit(a,2);
    print_list(res);
    deleteList(a);
    deleteList(res);

    a = NULL;
    res = NULL;
    a = createItem(1,a);
    a = createItem(2,a);
    a = createItem(3,a);
    a = createItem(4,a);
    a = createItem(5,a);
    a = createItem(1,a);
    print_list(a);
    res = cloneLimit(a,1);
    print_list(res);
    deleteList(a);
    deleteList(res);

    a = NULL;
    res = NULL;
    print_list(a);
    res = cloneLimit(a,1);
    print_list(res);
    deleteList(a);
    deleteList(res);



    return 0;
}
