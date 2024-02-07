#include<stdio.h>
#include<stdlib.h>


typedef struct bus{
    char platform;
    int platform_no;
    int passenger;
    int full;
}bus;

bus * push_array (bus * array, int * size , int * capacity , char platform , int platform_no , int pass){
    if(*size >= *capacity){
        if(*capacity==0) *capacity = 1 ;
        *capacity = (*capacity)*2;
        array = (bus *) realloc(array,(*capacity)*sizeof(bus));
    }
    array[*size].platform = platform;
    array[*size].platform_no = platform_no;
    array[*size].passenger = pass;
    array[*size].full = 0 ;
    (*size)++;
    return array;
}


int compare (bus * a , bus * b){
    if(a->platform != b->platform){
        return (a->platform > b->platform) - (b->platform > a->platform);
    }
    else{
        return (a->platform_no > b->platform_no) - (b->platform_no > a->platform_no);
    }
}

int main(){
    printf("Enter the number of events:\n");
    int events;
    if( scanf (" %d",&events)!=1){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    bus * list = NULL;
    int size = 0 , capacity = 0 ;
    printf("Enter events:\n");
    for(int i =0 ; i < events ; i++){
        char sign , platform;
        int platform_no , pass;
        if(scanf(" %c %c %d : %d",&sign,&platform,&platform_no,&pass)!=4 ||
        (sign != '+' && sign != '-') || platform < 'A' || platform >'J' || platform_no < 0 || 
        platform_no > 99){
            printf("Invalid input.\n");
            return EXIT_FAILURE;
        }
        int pushed = 0;
        if(sign == '+'){
            for(int j = 0 ; j < size ; j++){
                if(platform == list[j].platform && platform_no==list[j].platform_no){
                    list[j].passenger += pass;
                    pushed = 1;
                }
            }
            if(!pushed){
               list = push_array(list,&size,&capacity,platform,platform_no,pass);
               qsort(list,size,sizeof(bus),(int(*)(const void * , const void *))compare);
            }
        }
        if(sign == '-'){
            for(int j = 0 ; j < size ; j++){
                if(platform == list[j].platform && platform_no==list[j].platform_no){
                    // printf("have:%d , left: %d\n",list[j].passenger,pass);
                    if(pass<= list[j].passenger){
                        list[j].full++;
                    }
                    list[j].passenger -= pass;
                    if(list[j].passenger < 0){
                        list[j].passenger = 0 ;
                    }
                }
            }
        }

    }


    int max = 0 ;
    for(int i = 0 ; i < size ; i++){
        if(list[i].full > max){
            max = list[i].full;
        }
    }

    printf("Full buses left: %d, platform: ",max);

    int start = 1;
    for(int i = 0 ; i < size ; i++ ){
        if(list[i].full == max){
            if(!start){
                printf(" ,");
            }
            printf("%c%d",list[i].platform,list[i].platform_no);
            start = 0 ;
        }
    }
    printf("\n");



}

