#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 10

typedef struct cars{
    int floor;
    int position;
    int occupy;
    char number[max];
}cars;

int check_car_number(char * a){
    for(int i=0 ; i<8 ; i++){
        if(a[i]==' '){
            return 0;
        }
    }
    return 1;
}

cars * push_array(cars * array , size_t * size ,size_t * capacity , int floor , int position , char * car_no){
    if(*size>=*capacity){
        if(*capacity==0) *capacity=1;
        *capacity = (*capacity)*2;
        array = (cars *) realloc(array,(*capacity)*sizeof(cars));
    }
    array[*size].floor = floor;
    array[*size].position = position;
    array[*size].occupy = 1;
    strcpy(array[*size].number,car_no);
    (*size)++;
    return array;
}

int check_position(cars * list ,size_t * size ,int floor , int position){
    if(*size==0){
        return 1;
    }
    for(unsigned int i=0 ; i<*size ; i++){
        if(floor==list[i].floor && position==list[i].position && list[i].occupy==1){
            printf("Occupied by %s\n",list[i].number);
            return 0;
        }
    }
    return 1;
}

int is_there(cars * list , size_t * size , char * car){
    for(unsigned int i = 0 ; i<*size ; i++){
        if(strcmp(car,list[i].number)==0 && list[i].occupy==1){
            list[i].occupy=0;
            return 1;
        }
    }
    return 0;
}

int main(){
    printf("Size :\n");
    int floors , spaces;
    if(scanf("%d %d",&floors, &spaces)!=2 || floors <0 || spaces <0){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    char c;
    cars * list = NULL;
    size_t size = 0 , capacity = 0;
    int f , p;
    char car_no[max];
    int check = 0;
    while(scanf(" %c",&c)==1 && (c=='+' || c=='-')){
        if(c== '+'){
            if(scanf(" %d %d %s",&f,&p,car_no) !=3 
            || f < 0 || f >= floors || p < 0 || p >= spaces
            || !check_car_number(car_no)){
                printf("Invalid input1\n");
                return EXIT_FAILURE;
            }
            check = check_position(list,&size,f,p);
            list = push_array(list , &size , &capacity , f , p , car_no);
            if(check){
                printf("OK\n");
            }
        }
        if(c== '-'){
            if(scanf(" %s",car_no)!=1||!check_car_number(car_no)){
                printf("Invalid input2\n");
                return EXIT_FAILURE;
            }
            check = is_there(list,&size,car_no);
            if(check){
                printf("OK\n");
            }
            else{
                printf("Not found\n");
            }
        }
    }
    if(!feof(stdin)){
        printf("Invalid input3\n");
        return EXIT_FAILURE;
    }


    free(list);

    return EXIT_SUCCESS;
}

