#include<stdio.h>
#include<stdlib.h>


typedef struct sale{
    char letter;
    int amount;
    // int customer;
}sale;

sale * push_array (sale * array, int * size ,int * capacity , char letter , int amount){
    if(*size >= * capacity){
        if(*capacity == 0) *capacity = 1;
        *capacity = (*capacity ) * 2 ;
        array = (sale *) realloc (array, (*capacity) * sizeof(sale));
    }
    array[*size].letter = letter;
    array[*size].amount = amount;
    (*size)++;
    return array;
}


double round_to_two (double number){
    int temp = number * 100;
    double result = (double)temp/100;
    return result;
}

int main(){
    printf("Enter the number of transactions n:\n");
    int events;
    if(scanf("%d",&events)!=1 || events <=0 ){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("Enter individual sales:\n");
    char letter;
    int amount;
    sale * list = NULL;
    int size =0 , capacity = 0 ;
    for(int i = 0 ; i < events ; i++){
        if(scanf(" %c : %d",&letter,&amount)!=2 || letter < 65 || letter > 90 || amount <=0){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        int pushed = 0 ;
        for(int i = 0 ; i < size ; i++){
            if(letter==list[i].letter){
                list[i].amount += amount;
                pushed = 1 ;
            }
        }
        if(!pushed){
            list = push_array(list,&size,&capacity,letter,amount);
        }
    }

    for(int i = 0 ; i < size ; i++){
        printf("%c:%d\n",list[i].letter,list[i].amount);
    }

    double sum = 0 ;
    for(int i = 0 ; i < size ; i ++){
        sum += list[i].amount;
    }

    double average =  sum / (size) ;
    average = round_to_two(average);
    // printf("sum: %f , size : %d \n",sum,size);
    printf("The average sales per checkout is: %.2lf. Above average cash registers:",average);

    int found = 0;
    for(int i = 0 ; i < size ; i++){
        if(list[i].amount > average){
            if(i==0){
                printf(" ");
            }
            printf("%c",list[i].letter);
            found = 1;
        }
    }
    if(!found){
        printf("-");
    }
    printf("\n");


}

