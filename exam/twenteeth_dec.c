#include<stdio.h>
#include<stdlib.h>
#include<string.h>



char ** push_string(char ** array , size_t * size , size_t * capacity , char * string){
    if(*size >= *capacity ){
        if(*capacity==0) *capacity =1;
        *capacity = (*capacity) * 2;
        array = (char **) realloc(array,(*capacity)*sizeof(char *));
    }
    array[*size] = (char *) malloc(strlen(string)+1);
    strcpy(array[*size],string);
    (*size)++;
    return array;
}

int main(){
    char ** list = NULL;
    char ** queries = NULL;
    size_t list_size = 0 , list_capacity = 0;
    size_t query_size = 0 , query_capacity = 0;
    printf("Enter list\n");
    char * string = NULL;
    size_t string_size = 0;
    int l = 0 , q = 0;
    while(getline(&string,&string_size,stdin)!=EOF){
        if(string[0]=='#'){
            l = 1;
            q = 0;
            continue;
        }
        if(string[0]=='!'){
            l = 0;
            q = 1;
            continue;
        }
        if(l==1){
        list = push_string(list,&list_size,&list_capacity,string);
        }
        if(q==1){
        queries = push_string(queries,&query_size,&query_capacity,string);
        }
        
    }
    

    int * result = (int *) calloc(query_size,sizeof(int));

    // printf("query_size: %zu\n",query_size);
    // printf("list_size: %zu\n",list_size);
    // for(unsigned int i=0 ; i<query_size; i++){
    //     printf("%s\n",queries[i]);
    // }
    for(unsigned int i=0 ; i<query_size ; i++){
        for(unsigned int j= 0 ; j<list_size ; j++){
            // printf("query:%s\n",queries[i]);
            // printf("list:%s\n",list[j]);
            if(strcmp(queries[i],list[j])==0){
                result[i]++;
            }
        }
    }

    for(unsigned int i=0 ; i<query_size ; i++){
        free(queries[i]);
    }
    free(queries);
    for(unsigned int i=0 ; i<list_size ; i++){
        free(list[i]);
    }
    free(list);

    for(unsigned int i=0 ; i<query_size ; i++){
        if(i!=0){
            printf(", ");
        }
        printf("%d",result[i]);
    }
    printf("\n");
    free(result);

}

