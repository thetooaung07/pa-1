#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char ** push_array(char ** array , size_t * size ,size_t * capacity , char * storage){
	if(*size >= *capacity){
		if(*capacity==0) *capacity = 1;
		*capacity = (*capacity) * 2;
		array = (char **) realloc(array,(*capacity)*sizeof(char *));
	}
	array[*size] = (char *) malloc(strlen(storage)+1);
	strcpy(array[*size], storage);
	(*size)++;
	return array;
}


int main(){
	printf("Names:\n");
	char ** array = NULL;
	size_t  size =0 , capacity = 0;
	char ** first_name = NULL;
	size_t first_name_size=0 , first_name_capacity =0;
	char  * string = NULL;
	size_t string_size = 0;
	while(getline(&string, &string_size,stdin)!=EOF){
		char * temp = string;
		int first_word = 1;
		while(*temp){
			if(isspace(*temp)){
				temp++;
				continue;
			}
			char * word = (char *) malloc(strlen(string)+1);
			char * head = word;
			while(!isspace(*temp)){
				*word = *temp;
				word++;
				temp++;
			}
			*word ='\0';
			if(first_word){
				first_name = push_array(first_name,&first_name_size,&first_name_capacity,head);
			}
			array = push_array(array,&size,&capacity,head);
			free(head);
			first_word = 0;
		}
		string = NULL;
	}

	printf("size: %lu\n",size);


	int * result = (int *) calloc(first_name_size,sizeof(int));
	for(unsigned int i=0 ; i<first_name_size ; i++){
		for(unsigned int j=i ; j<size; j++){
			if(strcmp(first_name[i],array[j])==0){
				result[i]++;
			}
		}
	}

	for(unsigned int i=0 ; i<first_name_size ; i++){
		printf("%d\n",result[i]);
	}


	for(unsigned int i=0 ; i<first_name_size ; i++){
		printf(">%s<\n",first_name[i]);
		free(array[i]);
	}
	free(array);



	return 0;
}
