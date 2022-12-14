#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
	int process_rank, process_count, num;
	MPI_Status status;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);

	if(process_rank == 0){
		printf("Enter the value of num \n");
		scanf("%d", &num);

		MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else{
		MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		printf("Received %d by process %d", num, process_rank);
	}
	MPI_Finalize();
}
