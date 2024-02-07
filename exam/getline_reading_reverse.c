#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char * remove_newline(char * string){
    int length = strlen(string);
    if(length >0  && string[length-1]=='\n'){
        string[length-1] ='\0';
    }
    return string;
}


int main(){
    printf("Enter:\n");
    char * string = NULL;
    size_t string_size = 0;
    while(getline(&string,&string_size,stdin)!=EOF){
        string = remove_newline(string);
        int length = strlen(string);
        char * temp = string;
        while(*temp){
            if(!isalpha(*temp)){
                *temp ='\0';
            }
            temp++;
        }

        // printf("%s\n",string);
        // printf("%zu\n",string_size);
        // printf("length:%d\n",length);

        int start = 1 ;
        for( int i = length-2 ; i >= 0 ; i--){
            if(!string[i] && string[i+1]){
                if(!start){
                    printf(" ");
                }
                printf("%s",string+i+1);
                start = 0;
            }
            if(i==0 && isalpha(string[i])){
                printf(" %s",string);
            }
        }
        printf("\n");
        free(string);
        string = NULL;
        string_size = 0;
    }

    return 0;
}

