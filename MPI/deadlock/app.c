/*
 ____                 _ _            _    
|  _ \  ___  __ _  __| | | ___   ___| | __
| | | |/ _ \/ _` |/ _` | |/ _ \ / __| |/ /
| |_| |  __/ (_| | (_| | | (_) | (__|   < 
|____/ \___|\__,_|\__,_|_|\___/ \___|_|\_\

Write an MPI program to demonstrate deadlock and implement a solution to avoid deadlock

 */

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(){
    int rank, size, tag1 = 1, tag2 = 2;
    char outmsg[100] = "DITOE";
    char inmsg[100];
    MPI_Status stat;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, 1, tag2, MPI_COMM_WORLD, &stat);
    }
    else if(rank == 1){
        MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, 0, tag2, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, 0, tag1, MPI_COMM_WORLD, &stat);
    }

    printf("Rank %d received message %s from process %d with tag %d and error status %d \n", rank, inmsg, stat.MPI_SOURCE, stat.MPI_TAG, stat.MPI_ERROR);

    MPI_Finalize();
    return 0;

}

