/*
 ____                 _    ___      ____                 
/ ___|  ___ _ __   __| |  ( _ )    |  _ \ ___  _____   __
\___ \ / _ \ '_ \ / _` |  / _ \/\  | |_) / _ \/ __\ \ / /
 ___) |  __/ | | | (_| | | (_>  <  |  _ <  __/ (__ \ V / 
|____/ \___|_| |_|\__,_|  \___/\/  |_| \_\___|\___| \_/  

Write an MPI program to implement blocking send and recieve functions.

 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

int main(){
    char outmsg[100] = "Death is the only escape";
    char inmsg[100];
    MPI_Status stat;
    int rank, size;
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, 0, 1, MPI_COMM_WORLD, &stat);
    }
    printf("Task %d received a message %s from task %d with a tag %d and an error status of %d \n", rank, inmsg, stat.MPI_SOURCE, stat.MPI_TAG, stat.MPI_ERROR);

    MPI_Finalize();
    return 0;
}
