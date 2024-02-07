#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



int check_no(char * s){
    while(*s){
        if(isspace(*s)){
            return 0;
        }
        s++;
    }
    return 1;
}

typedef struct cars{
    int floor_no;
    int space_no;
    int occupied;
    char * register_number;
}cars;



cars * push_array (cars * array , int * size , int * capacity, int floor , int space , char * reg){
    if(*size >= * capacity){
        if(*capacity==0) * capacity = 1;
        *capacity = (* capacity) * 2;
        array = (cars *) realloc(array,(*capacity)*sizeof(cars));
     }
     array[*size].floor_no = floor;
     array[*size].space_no = space;
     array[*size].occupied = 1;
     array[*size].register_number = (char *) malloc(strlen(reg)+1);
     strcpy(array[*size].register_number,reg);
     (*size)++;
     return array;
}



int main(){
    printf("Size : \n");
    cars * list = NULL;
    int floors , spaces;
    if(scanf(" %d %d",&floors , &spaces)!=2 || floors <= 0 || spaces <= 0){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    char c ;
    int size = 0 , capacity = 0;
    printf("Enter the list:\n");
    while(scanf(" %c",&c)==1){
        if(c != '+' && c != '-'){
            printf("Invalid input\n");
            return EXIT_FAILURE;
        }
        int floor , space ;
        char reg_no[11];
        if(c=='+'){
            if(scanf(" %d %d %s", &floor , &space ,reg_no)!=3 || floor < 0 || floor >= floors || space<0 || space >= spaces || !check_no(reg_no)){
                printf("Invalid input\n");
                return EXIT_FAILURE;
            }
            int ok = 1;
            for(int i = 0 ; i < size ; i++){
                if(floor==list[i].floor_no && space==list[i].space_no && list[i].occupied==1){
                    printf("Occupied by %s\n",list[i].register_number);
                    ok = 0;
                }
            }
            if(ok){
                list = push_array(list,&size,&capacity,floor,space,reg_no);
                printf("OK\n");
            }
        }
        if(c=='-'){
            if(scanf(" %s",reg_no)!=1 || !check_no(reg_no)){
                printf("Invalid input\n");
                return EXIT_FAILURE;
            }
            int ok = 0;
            for(int i = 0; i < size ; i++){
                if(strcmp(reg_no,list[i].register_number)==0 && list[i].occupied==1){
                    ok = 1;
                    printf("OK\n");
                    list[i].occupied = 0;
                }
            }
            if(!ok){
                printf("Not Found\n");
            }
        }

    }
    if(!feof(stdin)){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

}

