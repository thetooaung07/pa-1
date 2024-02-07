#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int x;
    struct Node * next;
}Node;


Node * insert_End(Node * l , int x){
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->x = x;
    new_node->next = NULL;
    if(l==NULL){
        return new_node;
    }
    Node * current = l;
    while (current->next)
    {
        current=current->next;
    }
    current->next = new_node;
    return l;
}

Node * insert_Start(Node * l , int x){
    Node * new_node = (Node *) malloc(sizeof(Node));
    new_node->x = x;
    if(l==NULL){
        new_node->next = NULL;
        return new_node;
    }
    new_node->next = l;
    return new_node;
}



void recursion(Node * l){
    if(l==NULL){
        return;
    }
    recursion(l->next);
    printf("%d -> ",l->x);
}

void reverse_print(Node * l){
    recursion(l);
    printf("\n");
}

void print_list(Node *l){
    if(l==NULL){
        return;
    }
    while(l){
        printf("%d -> ",l->x);
        l = l->next;
    }
    printf("\n");
}


Node * reverse_list(Node * l){
    Node * previous = NULL;
    Node * current = l;
    while(current){
        Node * temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    return previous;
}

Node * divider(Node * l){
    Node * hare = l->next;
    Node * tortoise = l;
    while (hare->next)
    {
        hare = hare->next;
        if(hare->next){
            hare = hare->next;
            tortoise = tortoise->next;
        }
    }
    
    return tortoise;
}

Node * merge(Node * a, Node *b , int ascending){
    Node * sorted = NULL;
    int constant = 1;
    if(ascending == 0) constant = -1;
    if(constant * (a->x < b->x ) == 1){
        sorted = a;
        a = a->next;
    }
    else{
        sorted = b;
        b = b->next;
    }
    Node * head = sorted;
    while(a!=NULL && b!= NULL){
        if(constant * (a->x < b->x ) == 1){
            sorted->next = a;
            a = a->next;
            sorted = sorted->next;
        }
        else{
            sorted->next = b;
            b = b->next;
            sorted = sorted->next;
        }
    }
    if(a!=NULL){
        sorted->next = a;
    }
    if(b!=NULL){
        sorted->next = b;
    }
    return head;

}


Node * sort_list(Node * l , int ascending){
    if(l==NULL){
        return NULL;
    }
    if(l->next == NULL){
        return l;
    }

    Node * mid = divider(l);
    Node * temp = mid;
    mid = mid->next;
    temp->next = NULL;
    Node *l1 = sort_list(l,ascending);
    Node *l2 = sort_list(mid,ascending);
    return merge(l1,l2,ascending);

   
}


Node * remove_by_position(Node *l , int position){
    int current_position = 1;
    Node * current = l;
    while(current->next){
        if((current_position+1) == position ){
            Node * to_remove = current->next;
            current->next = current->next->next;
            current_position++;
            free(to_remove);
        }
        else{
            current=current->next;
            current_position++;
        }
    }
    if(position==1){
        Node * to_remove = l;
        l = l->next;
        free(to_remove);
    }

    return l;
}


Node * remove_duplicates(Node * l){
    l=sort_list(l,1);
    Node * current = l;
    while(current->next){
        if(current->x == current->next->x){
            Node * to_remove = current->next;
            current->next = current->next->next;
            free(to_remove);
        }
        else{
            current = current->next;
        }
    }
    return l;
}
void free_list(Node * l){
    while (l)
    {
        Node * to_free = l;
        l = l->next;
        free(to_free);
    }
}


int main(){
    Node * l = NULL;
    l = insert_Start(l,2);
    l = insert_End(l,6);
    l = insert_End(l,8);
    l = insert_Start(l,9);
    l = insert_Start(l,10);
    l = insert_Start(l,11);
    l = insert_Start(l,12);
    l = insert_End(l,3);
    print_list(l);
    reverse_print(l);
    print_list(l);
    l = reverse_list(l);
    print_list(l);
    l=sort_list(l,1);
    print_list(l);
    l = remove_by_position(l,1);
    print_list(l);
    free_list(l);
    l = NULL;

    printf("___Task 2____\n");
    l = insert_End(l,4);
    l = insert_End(l,2);
    l = insert_End(l,3);
    l = insert_End(l,2);
    l = insert_End(l,1);
    l = insert_End(l,3);
    l = insert_End(l,3);
    l = insert_End(l,4);
    print_list(l);
    l = remove_duplicates(l);
    print_list(l);
    free_list(l);






    return 0;
}

