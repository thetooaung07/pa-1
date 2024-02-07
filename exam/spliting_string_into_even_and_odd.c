#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char * remove_newline (char * string){
    int length = strlen(string);
    if(length > 0 && string[length-1]=='\n'){
        string[length-1] = '\0';
    }
    return string;
}


int main(){
    printf("Enter:\n");
    char * string = NULL;
    size_t string_size = 0 ;
    getline(&string,&string_size,stdin);
    // string = remove_newline(string);
    char * temp = string;
    char * head = temp;
    int length = strlen(string);
    while(*temp){
        if(!isalpha(*temp)){
            *temp = '\0';
        }
        temp++;
    }

    char * even = (char *) malloc(length+1);
    char * head_even = even;
    char * odd =  (char *) malloc(length+1);
    char * head_odd = odd;

    temp = head;
    while(length!=0){
        // printf("string_length: %lu\n",strlen(temp));
        int looped = 0 ;
        if(strlen(temp)%2==0){
            while(*temp){
                looped = 1;
                *even = *temp;
                even++;
                temp++;
                length--;
            }
            if(looped){
                *even =' ';
                even++;
            }
            temp++;
            length--;
        }
        else{
            printf("length: %lu\n",strlen(temp));
            while(*temp){
                looped = 1;
                *odd =  *temp;
                odd++;
                temp++;
                length--;
            }
            if(looped){
                *odd = ' ';
                odd++;
            }
            temp++;
            length--;
        }
    }
    *even ='\0';
    *odd ='\0';
    even = remove_newline(even);
    odd = remove_newline(odd);
    

    // free(head);
    printf("%s\n",head_even);
    printf("%s\n",head_odd);
    free(head);
    free(head_even);
    free(head_odd);



}


