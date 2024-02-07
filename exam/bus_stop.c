#include<stdio.h>
#include<stdlib.h>


typedef struct bus{
    char platform;
    int platform_no;
    int passenger;
    int left;
    int max;
}bus;

bus * push_arrive(bus * array, int * size , int * capacity, char platform, int num , int pass){
    if(*size>=*capacity){
        if(*capacity==0) *capacity = 1;
        *capacity = (*capacity)*2;
        array = (bus *) realloc(array,(*capacity)*sizeof(bus));
    }
    array[*size].left = 0 ;
    array[*size].platform = platform;
    array[*size].platform_no = num;
    array[*size].passenger = pass;
    array[*size].max = 0;
    (*size)++;
    return array;
}

int main(){
    bus * list = NULL;
    int size = 0 , capacity = 0;
    printf("Enter the number of events:\n");
    int events;
    if(scanf(" %d",&events)!=1){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("Enter events\n");
    for(int i = 0 ; i < events ; i++){
        char sign ;
        char platform;
        int platform_no , pass;

        if(scanf(" %c%c%d:%d",&sign,&platform,&platform_no,&pass)!=4 || (sign != '+' && sign != '-')||
                platform < 'A' || platform > 'J' 
                || platform_no < 0 || platform_no > 99 || pass <=0 ){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }

        if(sign == '+'){
            int have = 0;
            for(int i = 0 ; i < size ; i++){
                if(platform==list[i].platform && platform_no == list[i].platform_no){
                    list[i].passenger += pass;
                    have = 1;
                }
            }
            if(have==0){
            list = push_arrive(list,&size,&capacity,platform,platform_no,pass);
            }
        }

        if(sign == '-'){
            
            for(int i = 0 ; i < size ; i++){
                if(platform==list[i].platform && platform_no == list[i].platform_no){
                    if(pass > list[i].passenger){
                        printf("Invalid input.\n");
                        return EXIT_FAILURE;
                    }
                    list[i].passenger -= pass;
                    list[i].left += pass;
                }
            }
        }

    }


    int max = 0;
    for(int i = 0 ; i < size ; i++){
        if(list[i].left > max){
            max = list[i].left;
        }
        // printf("%c%d,\narrived:%d\nleft:%d\n",list[i].platform,list[i].platform_no,list[i].passenger,list[i].left);
    }

    printf("Most passengers departed: %d, ",max);

    int count = 0;
    for(int i =0 ; i < size ; i++){
        if(list[i].left==max){
            list[i].max = 1;
            count ++;
        }
    }
    printf("platform ");


    int start = 0 ;
    for(int i = 0 ; i < size ; i++){
        if(list[i].max==1){
            if(start!=0){
                printf(" ,");
            }
            start++;
            printf("%c%d",list[i].platform,list[i].platform_no);
        }
    }
    printf("\n");


    


}