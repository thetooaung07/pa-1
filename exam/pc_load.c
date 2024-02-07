#include<stdio.h>
#include<stdlib.h>


typedef struct computer{
    int load;
    int from;
    int to;
}computer;

computer * push_structure(computer * a , size_t * size , size_t * capacity , int l ,int f , int t){
    if(*size>=*capacity){
        if(*capacity==0) *capacity = 1;
        *capacity = (*capacity)*2;
        a = (computer *) realloc(a,(*capacity)*sizeof(computer));
    }
    
    a[*size].load = l;
    a[*size].from = f;
    a[*size].to = t;
    (*size)++;
    return a;
}


int main(){
    printf("Load:\n");
    int load , from , to;
    computer * a = NULL;
    size_t size = 0 , capacity = 0;
    while(scanf(" %d: %d..%d",&load , &from , &to)==3){
        a = push_structure(a,&size,&capacity,load,from,to);
    }
    if(!feof(stdin)){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    int max = a[0].from;
    
    for(unsigned int i = 0 ; i<size ; i++){
        // printf("load: %d, ",a[i].load);
        // printf("from: %d, ",a[i].from);
        // printf("to: %d\n",a[i].to);
        if(a[i].from > max){
            max = a[i].from;
        }
        if(a[i].to > max){
            max = a[i].to;
        }
    

    }

    int * result = (int *)calloc(max , sizeof(int));

    for(unsigned int i =0 ; i < size ; i++){
        for(int j = a[i].from ; j<a[i].to ; j++){
            result[j]+= a[i].load;
        }
    }
    
    int max_load = result[0];
    for(int i =1 ; i<max ; i++){
        if(result[i]>max_load){
            max_load = result[i];
        }
    }
    printf("Maximum load: %d\n",max_load);


    int start , end;
    for(int i =0 ; i < max ; i++){
        if(result[i]==max_load){
            start = i;
            for(int j=i ; j < max && result[j]==result[i];j++){
                end =j;
            }
            printf("%d..%d\n",start,end+1);
            i = end+1;
        }
    }


    free(result);
    free(a);

    return 0;
}

