/*
__     __        _                  _       _     _ _ _   _             
\ \   / /__  ___| |_ ___  _ __     / \   __| | __| (_) |_(_) ___  _ __  
 \ \ / / _ \/ __| __/ _ \| '__|   / _ \ / _` |/ _` | | __| |/ _ \| '_ \ 
  \ V /  __/ (__| || (_) | |     / ___ \ (_| | (_| | | |_| | (_) | | | |
   \_/ \___|\___|\__\___/|_|    /_/   \_\__,_|\__,_|_|\__|_|\___/|_| |_|
                                                                        
Write a program to show parallel vector addition
 */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    int n = 1e8;

    int *vector_a = (int*)malloc(sizeof(int)*n);
    int *vector_b = (int*)malloc(sizeof(int)*n);
    int *res_vector = (int*)malloc(sizeof(int)*n);
    int *ser_vector = (int*)malloc(sizeof(int)*n);

    for(int i = 0 ; i < n ; i++){
        vector_a[i] = rand() % 10;
        vector_b[i] = rand() % 10;
    }

    double start = omp_get_wtime();
#pragma omp parallel for
    for(int i = 0 ; i < n ; i++)
        res_vector[i] = vector_a[i] + vector_b[i];
    double end = omp_get_wtime();
    printf("Parallel Execution Time: %f \n", end - start);

    start = omp_get_wtime();
    for(int i = 0 ; i < n ; i++){
        ser_vector[i] = vector_a[i] + vector_b[i];
    }
    end = omp_get_wtime();
    printf("Serial Execution Time: %f \n", end - start);
    return 0;
}
