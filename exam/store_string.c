#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void remove_newline(char * string){
    int length = strlen(string);
    if(length>0 && string[length-1]=='\n'){
        string[length-1]='\0';
    }
}

char ** push_string_array(char ** string_array , size_t * size , size_t * capacity , char * string){
    if(*size>=*capacity){
        if(*capacity==0) *capacity = 1;
        *capacity = (*capacity) * 2;
        string_array = (char **) realloc(string_array , sizeof(char *)*(*capacity));
    }
    string_array[*size] = (char *) malloc(strlen(string)+1);
    strcpy(string_array[*size],string);
    (*size)++;
    return string_array;
}

int main(){
    char * string;
    size_t string_length;
    char ** string_array;
    size_t  size = 0 , capacity = 0;
    printf("Enter the string.\n");
    while(getline(&string,&string_length,stdin)!=EOF){
        remove_newline(string);
        string_array = push_string_array(string_array,&size,&capacity,string);
    }

    for(unsigned int i = 0 ; i<size ; i++){
        printf("%s\n",string_array[i]);
    }
}

