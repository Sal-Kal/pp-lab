#include <mpi.h>
#include <stdio.h>

double func(double x) { return x * x; }

double Trap(double a, double b, int h) {
  double i, j;
  double sum = 0.0, area;
  for (i = a; i < b; i += h) {
    j = i + h;
    area = 0.5 * h * (func(i) + func(j));
    sum += area;
  }

  return sum;
}
int main() {

  int rank, size;
  MPI_Status status;
  double a, b, h, n;
  double n_p, a_p, b_p, c_p, sum_p, final_sum = 0.0;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (rank == 0) {
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &n);

    n_p = n / size;

    h = (b - a) / n;
  }
  MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&h, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  a_p = a + rank * h * n_p;
  b_p = a_p + h * n_p;

  sum_p = Trap(a_p, b_p, h);

  MPI_Allreduce(&sum_p, &final_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  printf("Area is %lf, for process %d\n", final_sum, rank);
  MPI_Finalize();
  return 0;
}
