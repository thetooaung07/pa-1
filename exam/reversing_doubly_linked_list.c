#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int x;
    struct Node * next;
    struct Node * previous;
}Node;

Node * insert_end(Node * l , int x){
    Node * new_node = (Node *) malloc(sizeof(Node));
    new_node->x = x;
    new_node->next = NULL;
    if(l==NULL){
        new_node->previous = NULL;
        return new_node;
    }
    
    Node * current = l;
    while(current->next){
        current = current->next;
    }
    current->next = new_node;
    new_node->previous  = current;

    return l;
}

Node * insert_Start(Node * l , int x){
    Node * new_node = (Node *) malloc(sizeof(Node));
    new_node->x = x;
    new_node->previous = NULL;
    if(l==NULL){
        new_node->next = NULL;
        return new_node;
    }
    new_node->next = l;
    l->previous = new_node;
    return new_node;
}

void printlist(Node *l){
    if(l==NULL){
        return;
    }
    while(l){
        printf("%d -> ",l->x);
        l = l->next;
    }
    printf("\n");
}


void print_reverse(Node *l){
    while(l->next){
        l = l->next;
    }
    while(l){
        printf("%d -> ", l->x);
        l = l->previous;
    }
    printf("\n");
}

Node * reverse_list(Node *l){
    if(l==NULL){
        return NULL;
    }
    if(l->next==NULL){
        return l;
    }
    while(l->next){
        l = l ->next;
    }
    
    Node * head = l;
    Node * to_reverse = NULL;
    while(l){
        to_reverse = l;
        l = l->previous;
        to_reverse->previous = to_reverse->next;
        to_reverse->next = l;
        // l->previous = to_reverse;
    }
    return head;
}

int main(){
    Node * l = NULL;
    l = insert_end(l,3);
    l = insert_end(l,5);
    l = insert_Start(l,6);
    l = insert_Start(l,7);
    l = insert_Start(l,8);
    l = insert_Start(l,9);
    printlist(l);
    // print_reverse(l);
    l = reverse_list(l);
    printlist(l);
    print_reverse(l);


}

