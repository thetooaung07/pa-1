#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char * remove_newline ( char * string){
    int length = strlen(string);
    if(length > 0 && string[length-1]=='\n'){
        string[length-1] = '\0';
    }
    return string;
}


int main(){
    char * string_one = NULL ;
    char * string_two = NULL;
    size_t string_one_size = 0 , string_two_size = 0;
    getline(&string_one,&string_one_size,stdin);
    getline(&string_two,&string_two_size,stdin);
    char * result  = (char *) malloc (strlen(string_one)+strlen(string_two)+5);
    char * head  = result;
    char * temp1 = string_one;
    char * temp2 = string_two;
    temp1 = remove_newline(temp1);
    temp2 = remove_newline(temp2);
    while(*temp1 || *temp2){
        if(*temp1){
            while(*temp1 && !isalpha(*temp1)){
                temp1++;
            }
            while(*temp1 && isalpha(*temp1)){
                *result = *temp1;
                result++;
                temp1++;
            }
            *result = ' ';
            result++;
        }
        if(*temp2){
            while(*temp2 && !isalpha(*temp2)){
                temp2++;
            }
            while(*temp2 && isalpha(*temp2)){
                *result = *temp2;
                result++;
                temp2++;
            }
            *result = ' ';
            result++;
        }
    }
    *result = '\0';

    printf("Result:\n%s\n",head);
    free(head);
    free(string_one);
    free(string_two);
    return 0;
}


