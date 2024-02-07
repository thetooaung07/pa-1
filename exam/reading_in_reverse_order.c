#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>





int main(){

    char c ;
    char * result = NULL;
    int capacity = 1 , size = 1;
    while((c=getc(stdin))!='\n'){
        if(!isalpha(c)){
            c='\0';
        }
        if(size>=capacity){
            capacity = capacity * 2 ;
            result = (char *) realloc(result,capacity);
        }
        result[size] = c;
        size++;
    }

    result[0] = result[size] = '\0';

    int start = 1 ;
    for(int i = size-2 ; i >= 0 ; i--){
        if(!result[i] && result[i+1]){
            if(!start){
                printf(" ");
            }
            printf("%s",result+i+1);
            start = 0;
        }
    }
    printf("\n");

}

// char ** push_array(char ** array, int * size , int * capacity , char * word){
//     if(*size>=*capacity){
//         if(*capacity==0) *capacity=1;
//         *capacity = (*capacity)*2;
//         array = (char **)realloc(array,(*capacity)*sizeof(char *));
//     }
//     array[*size] = (char *) malloc(strlen(word)+1);
//     strcpy(array[*size],word);
//     (*size)++;
//     return array;
// }

// char ** reverse_array(char ** array , int n){
//     char ** reversed = NULL;
//     int size = 0  , capacity = 0;
//     for(int i = n-1 ; i>=0 ; i--){
//         reversed = push_array(reversed,&size,&capacity,array[i]);
//     }
//     free(array);
//     return reversed;
// }


// int main(){
//     char * string;
//     size_t string_size = 0 ;
//     char ** list = NULL;
//     int size = 0 , capacity = 0 ;
//     getline(&string,&string_size,stdin);
//     if(string_size==0){
//         printf("NULL STRING\n");
//         return EXIT_SUCCESS;
//     }

//     char * word = NULL;
//     char * temp = string;
//     while(*temp){
//         if(!isalpha(*temp)){
//             temp++;
//             continue;
//         }

//         word = (char *) malloc(strlen(string)+1);
//         char * head = word;
//         while (isalpha(*temp))
//         {
//             *word++ = *temp++;
//         }
//         *word = '\0';
//         list = push_array(list,&size,&capacity,head);
//         free(head);
//     }

//     list = reverse_array(list,size);

//     for(int i = 0 ; i < size ; i++){
//         if(i!=0){
//             printf(" ");
//         }
//         printf("%s",list[i]);
//     }
//     printf("\n");

//     return 0;
// }


