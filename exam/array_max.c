#include<stdlib.h>
#include<stdio.h>

int ** push_array(int **q,size_t * size ,size_t * capacity , int a, int b , int k){
    if(*size>=*capacity){
        if(*capacity==0) *capacity=1;
        *capacity = (*capacity) * 2;
        q = (int **) realloc(q,(*capacity)*sizeof(int *));
    }
    q[*size] = (int *)malloc(sizeof(int)*3);
    q[*size][0] = a;
    q[*size][1] = b;
    q[*size][2] = k;
    (*size)++;
    return q;
}

int intcmp(const int *a , const int *b){
    return (*a<*b)-(*b<*a);
}



long array_manipulation(int ** q ,size_t size ,int n){
    long * result = (long *) calloc(n+1,sizeof(long));
    for(unsigned i = 0 ; i < size ; i++){
        result[q[i][0]-1] += q[i][2];
        result[q[i][1]] -= q[i][2];
    }

    long max = result[0];
    long count = 0;
    for(int i = 0 ; i<n ; i++){
        count += result[i];
        if(count > max ) max = count;
    }
    free(result);
    return max;
}


int main(){
    int ** q = NULL;
    size_t size = 0 , capacity = 0;
    int a , b , k;
    while(scanf(" %d %d %d",&a,&b,&k)==3){
        q = push_array(q,&size,&capacity,a,b,k);
    }
    if(!feof(stdin)){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    for(unsigned int i = 0 ; i <size ; i++){
           printf("a: %d , b: %d , k: %d \n",q[i][0],q[i][1],q[i][2]);
    }


    // printf("Enter the size of array.\n");
    // int n;
    // if(scanf("%d",&n)!=1){
    //     printf("Invalid input.\n");
    //     return EXIT_FAILURE;
    // }

    int n = 4;

    long max;
    max = array_manipulation(q,size,n);
    printf("max:%ld\n",max);

    for(unsigned int i = 0 ; i < size ; i++){
        free(q[i]);
    }
    free(q);
}

