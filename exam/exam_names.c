// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<ctype.h>

// char * remove_newline(char * string){
//     int length = strlen(string);
//     if(length > 0 && string[length-1]=='\n'){
//         string[length-1] = '\0';
//     }
//     return string;
// }


// typedef struct enroll{
//     char * name;
//     char ** sorted;
//     int items;
//     int come;
// }enroll;

// typedef struct present{
//     char * name;
//     char ** sorted;
//     int items;
//     int registered;
// }present;


// int stringcmp(char ** a , char ** b){
//     if(strcasecmp(*a,*b)>=0){
//         return 1;
//     }
//     else{
//         return -1;
//     }
// }

// char ** push_array(char ** array, int * size , int * capacity , char * string){
//     if(*size >= *capacity){
//         if(*capacity == 0 ) *capacity = 1;
//         *capacity = (*capacity) * 2;
//         array = (char **) realloc(array , (*capacity) * sizeof(char *));
//     }
//     array[*size] = (char *) malloc(strlen(string)+1);
//     strcpy(array[*size],string);
//     (*size)++;
//     return array;
// }

// enroll * push_enroll(enroll * array, int * size , int * capacity , char * string){
//     if(*size >= * capacity){
//         if(*capacity==0) *capacity = 1;
//         *capacity = (*capacity) * 2;
//         array = (enroll *) realloc (array,(*capacity)*sizeof(enroll));
//     }
//     array[*size].name = (char *) malloc(strlen(string)+1);
//     strcpy(array[*size].name,string);
//     array[*size].come = 0;

//     char * temp = string;
//     array[*size].sorted = NULL;
//     array[*size].items = 0;
//     int s_capacity = 0 ;
//     while(*temp){
//         if(isspace(*temp)){
//             temp++;
//             continue;
//         }
//         char * word = (char *) malloc(strlen(string)+1);
//         char * head = word;
//         while(!isspace(*temp) && *temp){
//             *word = *temp;
//             word++;
//             temp++;
//         }
//         *word = '\0';
//         array[*size].sorted = push_array(array[*size].sorted,&(array[*size].items),&s_capacity,head);
//         free(head);
//     }
//     qsort(array[*size].sorted,array[*size].items,sizeof(char *),(int(*)(const void * , const void *))stringcmp);
//     (*size)++;
//     return array;
// }


// present * push_present(present * array, int * size , int * capacity , char * string){
//     if(*size >= * capacity){
//         if(*capacity==0) *capacity = 1;
//         *capacity = (*capacity) * 2;
//         array = (present *) realloc (array,(*capacity)*sizeof(present));
//     }
//     array[*size].name = (char *) malloc(strlen(string)+1);
//     strcpy(array[*size].name,string);
//     array[*size].registered = 0;

//     char * temp = string;
//     array[*size].sorted = NULL;
//     array[*size].items = 0;
//     int s_capacity = 0 ;
//     while(*temp){
//         if(isspace(*temp)){
//             temp++;
//             continue;
//         }
//         char * word = (char *) malloc(strlen(string)+1);
//         char * head = word;
//         while(!isspace(*temp) && *temp){
//             *word = *temp;
//             word++;
//             temp++;
//         }
//         *word = '\0';
//         array[*size].sorted = push_array(array[*size].sorted,&(array[*size].items),&s_capacity,head);
//         free(head);
//     }
//     qsort(array[*size].sorted,array[*size].items,sizeof(char *),(int(*)(const void * , const void *))stringcmp);
//     (*size)++;
//     return array;
// }


// int compare(char ** a , int a_items , char ** b , int b_items){
//     if(a_items != b_items){
//         return 0;
//     }

//     for(int i =0 ; i < a_items ; i++){
//         if(strcasecmp(a[i],b[i])!=0){
//             return 0;
//         }
//     }
    
//     return 1;
    

// }

// void free_enroll ( enroll  * array , int size){
//     for(int i = 0 ; i < size ; i++ ){
//         free(array[i].name);
//         for(int j = 0 ; j < array[i].items ; j++){
//             free(array[i].sorted[j]);
//         }
//         free(array[i].sorted);
//     }
//     free(array);
// }

// void free_present ( present * array , int size ){
//     for( int i = 0 ; i < size ; i++ ){
//         free(array[i].name);
//         for(int j = 0 ; j < array[i].items ; j++){
//             free(array[i].sorted[j]);
//         }
//         free(array[i].sorted);
//     }
//     free(array);
// }


// void freeing(enroll * R_list , int R_size, present * P_list , int P_size){
//     free_enroll( R_list , R_size);
//     free_present( P_list , P_size);
//     free(string);
// }



// int main(){

//     char * string = NULL;
//     size_t string_sie = 0;

//     int change = 0 ;

//     enroll * R_list = NULL;
//     int R_size = 0  , R_capacity = 0;
    
//     present * P_list = NULL;
//     int P_size = 0 , P_capacity = 0;

//     while(getline(&string,&string_sie,stdin)!=EOF){
//         if((string[0]!= 'R' && string[0]!='P')||string[1]!=':' || string[2]!=' '){
//     freeing( R_list , R_size , P_list , P_size , string);
//             printf("Invalid input.\n");
//             return EXIT_FAILURE;
//         }
//         if(string[0]=='P'){
//             change = 1;
//         }
//         if(change && string[1]=='R'){
//     freeing( R_list , R_size , P_list , P_size , string);
//             printf("Invalid input.\n");
//             return EXIT_FAILURE;
//         }        

//         string = remove_newline(string);

//         if(string[0]=='R'){
//             R_list = push_enroll(R_list, &R_size, &R_capacity, string+3);
//         }
//         if(string[0]=='P'){
//             P_list = push_present(P_list , &P_size , &P_capacity, string+3);
//         }

//     }


//     freeing( R_list , R_size , P_list , P_size , string);


//     // printf("R:\n");
//     // for(int i = 0 ; i < R_size ; i++){
//     //     printf("Name: %s , items: %d \n",R_list[i].name,R_list[i].items);
//     //     for(int j = 0 ; j < R_list[i].items ; j++){
//     //         printf("%s - ",R_list[i].sorted[j]);
//     //     }
//     //     printf("\n");
//     // }

//     // printf("P:\n");
//     // for(int i = 0 ; i < P_size ; i++){
//     //     printf("Name: %s , items: %d \n",P_list[i].name,P_list[i].items);
//     //     for(int j = 0 ; j < P_list[i].items ; j++){
//     //         printf("%s - ",P_list[i].sorted[j]);
//     //     }
//     //     printf("\n");
//     // }


//     for(int i = 0 ; i < R_size ; i++){
//         for(int j =0 ; j < P_size ; j++){
//             if(compare(R_list[i].sorted,R_list[i].items,P_list[j].sorted,P_list[j].items) && R_list[i].come ==0 && P_list[j].registered==0){
//                 printf("%d - %d \n",R_list[i].items,P_list[j].items);
//                 printf("%s -  %s \n",R_list[i].name ,P_list[j].name);
//                 R_list[i].come = 1;
//                 P_list[j].registered = 1;
//             }
//         }
//     }

//     printf("Absent:\n");
//     for(int i = 0; i < R_size; i++) {
//         if(!R_list[i].come)
//         printf("*%s\n",R_list[i].name);
//     }
//     printf("Without reg:\n");
//     for(int i = 0; i < P_size; i++) {
//         if(!P_list[i].registered)
//         printf("*%s\n", P_list[i].name);
//     }




//     return 0;
// }


#include<stdio.h>

int main(){
    printf("Hello!");
}
