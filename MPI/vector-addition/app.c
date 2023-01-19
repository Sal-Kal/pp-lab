/*
__     __        _                  _       _     _ _ _   _             
\ \   / /__  ___| |_ ___  _ __     / \   __| | __| (_) |_(_) ___  _ __  
 \ \ / / _ \/ __| __/ _ \| '__|   / _ \ / _` |/ _` | | __| |/ _ \| '_ \ 
  \ V /  __/ (__| || (_) | |     / ___ \ (_| | (_| | | |_| | (_) | | | |
   \_/ \___|\___|\__\___/|_|    /_/   \_\__,_|\__,_|_|\__|_|\___/|_| |_|

Write a MPI program to implement Vector Addition of two vectors to generate resultant vector using Scatter and Gather operations.

 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(){
    int rank, size;
    int n = 100;
    int a[100], b[100], c[100];

    printf("Vector 1 : \n");
    for(int i = 0 ; i < n ; i++){
        a[i] = rand() % 10;
        printf("%d ", a[i]);
    }

    printf("\n");

    printf("Vector 2 : \n");
    for(int i = 0 ; i < n ; i++){
        b[i] = rand() % 10;
        printf("%d ", b[i]);
    }

    printf("\n");

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int subsize = n / size;
    int * ap = (int *)malloc(sizeof(int) * subsize);
    int * bp = (int *)malloc(sizeof(int) * subsize);
    int * cp = (int *)malloc(sizeof(int) * subsize);

    MPI_Scatter(a, subsize, MPI_INT, ap, subsize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, subsize, MPI_INT, bp, subsize, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0 ; i < subsize ; i++)
        cp[i] = ap[i] + bp[i];

    MPI_Gather(cp, subsize, MPI_INT, c, subsize, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Result: \n");
        for(int i = 0 ; i < n ; i++)
            printf("%d ", c[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
