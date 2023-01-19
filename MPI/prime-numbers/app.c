/*
 ____       _                  _   _                 _                   
|  _ \ _ __(_)_ __ ___   ___  | \ | |_   _ _ __ ___ | |__   ___ _ __ ___ 
| |_) | '__| | '_ ` _ \ / _ \ |  \| | | | | '_ ` _ \| '_ \ / _ \ '__/ __|
|  __/| |  | | | | | | |  __/ | |\  | |_| | | | | | | |_) |  __/ |  \__ \
|_|   |_|  |_|_| |_| |_|\___| |_| \_|\__,_|_| |_| |_|_.__/ \___|_|  |___/
                                                                         
Write an MPI program to generate all prime numbers till n

 */

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int isprime(int x){
    if(x == 0) return 0;
    if(x == 1) return 0;
    if(x == 2) return 1;

    for(int i = 2 ; i*i <= x ; i++){
        if(x % i == 0)
            return 0;
    }
    return 1;
}

int main(){
    int size, rank;
    int n = 179;
    int *globaldata = (int *)malloc(sizeof(int) * n);
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i = 0 ; i < n ; i++)
        globaldata[i] = i + 1;
    int itern = (n/size) + 1;
    printf("\nrank %d itern %d size %d n %d \n", rank, itern, size, n);
    for(int i = (rank * itern) ; i < ((rank + 1)*itern) ; i++){
        if(i > n) break;
        if(isprime(globaldata[i])){
            printf("%d ",globaldata[i]);
        }
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}
