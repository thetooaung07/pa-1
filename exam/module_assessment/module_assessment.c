#include<stdio.h>
#include<stdlib.h>


int * push_number(int * numbers , int * size , int * capacity, int a){
    if(*size >= * capacity){
        if(*capacity==0) * capacity = 1;
        *capacity = (* capacity) * 2 ;
        numbers = (int *) realloc (numbers,sizeof(int)*(*capacity));
    }
    numbers[*size] = a;
    (*size)++;
    return numbers;
}

int main(){
    printf("Points:\n");
    int * numbers = NULL;
    int size = 0 , capacity = 0;
    char start , end;
    if(scanf(" %c",&start)!=1 || start != '{'){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    int a;
    while(1){
        if(scanf(" %d %c",&a , &end)!=2){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        if( a < 0 || a > 1000000000){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        if(end != ',' && end !='}'){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        numbers = push_number(numbers,&size,&capacity,a);
        if(end=='}'){
            break;
        }
    }

    if(size == 0){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Intervals:\n");
    
    char open, close ;
    int b , c ;
    while(scanf(" %c %d ; %d %c",&open , &b , &c , &close)==4){
        if((open != '<' && open != '(') || (close != '>' && close != ')')){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        int count = 0;
        if(open == '('){
            b = b+1;
        }
        if(close == ')'){
            c = c-1;
        }

        for(int i = 0 ; i < size ; i++){
            if(numbers[i]>=b && numbers[i]<=c){
                count++;
            }
        }

        printf(" -> %d\n",count);

    }
    if(!feof(stdin)){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }


    return 0;
}

