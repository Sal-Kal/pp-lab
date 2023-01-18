/*
__     __    _                     __         _ 
\ \   / /_ _| |_   _  ___    ___  / _|  _ __ (_)
 \ \ / / _` | | | | |/ _ \  / _ \| |_  | '_ \| |
  \ V / (_| | | |_| |  __/ | (_) |  _| | |_) | |
   \_/ \__,_|_|\__,_|\___|  \___/|_|   | .__/|_|
                                       |_|      

Estimate the value of pi from the given formula.
Parallelize the code by removing loop carried dependency and record both serial and parallell execution times.

*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

#define NUM_STEPS 10000000

int main(){
    // Serial
    double pi = 0;
    double start = omp_get_wtime();
    for(int k = 0 ; k < NUM_STEPS ; k++){
        pi += pow(-1,k)/((2*k) + 1);
    }
    pi = 4 * pi;
    double end = omp_get_wtime();
    double time = end - start;
    printf("Value of pi is: %f \n", pi);
    printf("Serial Time for execution: %f \n", time);

    // Parallel
    pi = 0;
    start = omp_get_wtime();
    double thread[8];
#pragma omp parallel for num_threads(8)
    for(int k = 0 ; k < NUM_STEPS ; k++){
        int t = omp_get_thread_num();
        thread[t] += pow(-1,k)/((2*k) + 1);
    }
    for(int i = 0 ; i < 8 ; i++)
        pi += thread[i];

    pi = 4 * pi;
    end = omp_get_wtime();
    time = end - start;
    printf("Value of pi is: %f \n", pi);
    printf("Parallel Time for execution: %f \n", time);
    return 0;
}
