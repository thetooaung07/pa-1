#include<stdio.h>
#include<stdlib.h>




int main(){
    int test_cases;
    scanf("%d",&test_cases);
    for(int i = 0 ; i < test_cases ; i++){
        int N;
        scanf(" %d",&N);
        int * B;
        int B_sum;
        B = (int *) malloc(sizeof(int)*N);
        for(int j=0 ; j<N ; j++){
            scanf(" %d",&B[j]);
        }
        
        
        
        int * A = (int *) calloc(N,sizeof(int));

        int a = 1;
        int check = 0;
        for(int k=0 ; k<N ; k++){
            for(int l=k+1 ; l<N ; l++){
                if(B[l]==B[k] && A[l]==0 && B[l]>check){
                    check++;
                    A[l]=a;
                }
            }
            if(A[k]==0){
                A[k]=a;
                check =0;
                a++;
            }

        }

        for(int p=0 ; p<N ; p++){
            printf("%d ",A[p]);
        }
        printf("\n");
        
        
    }
    return 0;
}
