#include<stdio.h>
#include<stdlib.h>


int intcmp(int * a , int * b){
    return (*a < *b) - (*b < *a );
}

int main(){
    int a[5] = {2,4,1,2,7};
    int target = 7;
    int i = 0 ;
    int j = i + 1;
    int sum = 0 ;
    int count = 0;

    for(int i =0 ; i < 5 ; i++){
        sum+= a[i];
    }
    if(sum == target){
        count = 1;
        return EXIT_SUCCESS;
    }
    if(sum < target){
        printf("No possible way!\n");
        return EXIT_FAILURE;
    }

    sum = 0;
    while(i<5){
        sum = a[i];
        while(sum<target){
            sum += a[j];
            j++;
        }
        while(sum>target){
            sum -= a[i];
            i++;
        }
        if(sum==target){
            count++;
            sum = 0;
            i++;
            j = i + 1;
        }
    }


    printf("Count: %d\n",count);
}