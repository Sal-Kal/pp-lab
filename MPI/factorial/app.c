/*
 _____          _             _       _ 
|  ___|_ _  ___| |_ ___  _ __(_) __ _| |
| |_ / _` |/ __| __/ _ \| '__| |/ _` | |
|  _| (_| | (__| || (_) | |  | | (_| | |
|_|  \__,_|\___|\__\___/|_|  |_|\__,_|_|

Wrtie an MPI program to find factorial of a number using Broadcast and Reduce operation.
 */

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int n, rank, size;
    n = 7;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int global;
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int localprod = 1;
    int len = (n/size) + 1;
    for(int i = 1 ; i <= len ; i++){
        printf("Rank: %d len: %d i: %d \n n: %d \n", rank, len, i, n);
        int val = (rank * len) + i;
        printf("Rank: %d val: %d \n", rank, val);
        if(val <= n)
            localprod *= val;
        else break;
    }

    printf("LOCAL PRD: %d \n", localprod);
    MPI_Reduce(&localprod, &global, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if(rank == 0)
        printf("Factorial of %d is %d \n", n, global);

    MPI_Finalize();
    return 0;
}
