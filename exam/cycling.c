#include<stdio.h>
#include<stdlib.h>


typedef struct route{
    int start_index;
    int end_index;
    int distance_difference;
    int descent_difference;
    int max;
}route;

typedef struct points{
    int distance;
    int descent;
}points;


route * push_route(route * array , int * size , int * capacity,
                    int start_index , int end_index , int distance_difference , int descent_difference){
        
    if(*size>=*capacity){
        if(*capacity==0) *capacity = 1;
        *capacity = (*capacity) * 2;
        array = (route *) realloc(array, (*capacity) * sizeof(route));
    }
    array[*size].start_index = start_index;
    array[*size].end_index = end_index;
    array[*size].distance_difference = distance_difference;
    array[*size].descent_difference = descent_difference;
    array[*size].max = 0;
    (*size)++;
    return array;
}

points * push_array(points * array, int * size , int * capacity , int distance , int descent){
    if(*size>=*capacity){
        if(*capacity==0) *capacity = 1;
        *capacity = (*capacity) * 2;
        array = (points *) realloc(array, (*capacity) * sizeof(points));
    }
    array[*size].distance = distance;
    array[*size].descent = descent;
    (*size)++;
    return array;
}

int main(){
    points * list = NULL;
    route * cycling = NULL;
    int size = 0 , capacity = 0;
    int cycling_size = 0 , cycling_capacity = 0;
    printf("Cycle route:\n");
    int start;
    if(scanf("%d",&start)!=1){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    list = push_array(list,&size,&capacity,0,start);

    char plus;
    while(scanf(" %c",&plus)==1){
        int dis , des;
        if(scanf(" %d,%d",&dis,&des)!=2){
            printf("Invalid input\n");
            return EXIT_FAILURE;
        }
        list = push_array(list,&size,&capacity,dis,des);
    }
    if(!feof(stdin)){
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    // for(int i = 0 ; i < size ; i++){
    //     printf("+ %d,%d\n",list[i].distance,list[i].descent);
    // }

    for(int i = 0 ; i<size ;i++){
        for(int j = i+1 ; j < size ; j++){
            if(list[j].descent<list[i].descent){
                cycling = push_route (cycling,&cycling_size,&cycling_capacity,i,j,
                list[j].distance-list[i].distance,list[i].descent-list[j].descent);    
            }
        }
    }

    if(cycling==NULL){
        printf("Not Found\n");
        return EXIT_SUCCESS;
    }

    int max = cycling[0].descent_difference;
    int max_distance = 0;
    for(int i = 1 ; i < cycling_size ; i++){
        // printf("start: %d , end: %d , %d km , descent : %d\n",list[cycling[i].start_index].distance,list[cycling[i].end_index].distance,cycling[i].distance_difference,cycling[i].descent_difference);
        if(cycling[i].descent_difference >= max){
            max = cycling[i].descent_difference;
            if(cycling[i].distance_difference > max_distance){
                max_distance = cycling[i].distance_difference;
            }
            // printf("max_distance: %d\n",max_distance);
        }
    }

    for(int i = 0 ; i < cycling_size ; i++){
        if(cycling[i].descent_difference==max){
            if(cycling[i].distance_difference==max_distance){
                cycling[i].max = 1;
            }
        }
    }

    int max_id = 0;
    int count = 0;
    for(int i = 0 ; i < cycling_size ; i++){
        if(cycling[i].max==1){
            max_id= i;
            count++;
        }
    }

    printf("%d km, descent: %d m, variants: %d\n",cycling[max_id].distance_difference,cycling[max_id].descent_difference,count);
    for(int i=0 ; i < cycling_size ; i++){
        if(cycling[i].max==1){
            printf("+ %d (%d) -> + %d (%d)\n",list[cycling[i].start_index].distance,list[cycling[i].start_index].descent,
                                            list[cycling[i].end_index].distance,list[cycling[i].end_index].descent);
        }
    }

    
    free(cycling);
    free(list);
    return 0;
}
