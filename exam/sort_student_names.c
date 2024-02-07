#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct student{
    char Name[65];
    int year;
    int month;
    int day;
    int study_year;
}student;


student * push_array (student * array, int * size , int * capacity ,char * name , int year , int month , int day , int study_year){
    if(*size >= * capacity){
        if(*capacity==0) *capacity = 1;
        (*capacity) = (*capacity) * 2;
        array = (student *) realloc(array,(*capacity)*sizeof(student));
    }
    array[*size].year = year;
    array[*size].month = month;
    array[*size].day = day;
    array[*size].study_year = study_year;
    strcpy(array[*size].Name,name);
    (*size)++;
    return array;
}

int compare(student * a , student * b){
    // printf("%d %d\n", a->study_year, b->study_year);
    return (a->study_year > b->study_year) - (b->study_year > a->study_year);
}

void bubbleSort(student * list, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(list[j].study_year > list[j+1].study_year) {
                student tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}


int compare_birthday(student * a , student *b){
    if(a->year != b->year){
        return (a->year > b->year) - (b->year > a->year);
    }
    else{
        if(a->month != b->month){
            return (a->month > b->month) - (b->month > a->month);
        }
        else{
            if(a->day != b->day){
                return (a->day > b->day) - (b->day > a->day);
            }
        }
    }
    return 0;
}

int main(){
    printf("Enter:\n");
    char name[65];
    student * list = NULL;
    int size = 0 , capacity = 0;
    int year , month , day , study_year ;
    while(scanf(" %64s %4d-%02d-%02d %d",name,&year,&month,&day,&study_year)==5){
        list = push_array ( list , &size , &capacity, name , year , month , day , study_year);
    }
    if(!feof(stdin)){
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("\n");

    qsort(list , size , sizeof(student),(int(*)(const void * , const void *))compare);

    for(int i = 0 ; i < size ; i++){
        printf("%s %4d-%02d-%02d %d\n",list[i].Name,list[i].year,list[i].month,list[i].day,list[i].study_year);
    }


    printf("\n");

    qsort(list , size , sizeof(student),(int(*)(const void * , const void *))compare_birthday);

    for(int i = 0 ; i < size ; i++){
        printf("%s %4d-%02d-%02d %d\n",list[i].Name,list[i].year,list[i].month,list[i].day,list[i].study_year);
    }



    return 0;
}

