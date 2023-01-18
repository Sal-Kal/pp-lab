/*
 _____ _ _                                _ 
|  ___(_) |__   ___  _ __   __ _  ___ ___(_)
| |_  | | '_ \ / _ \| '_ \ / _` |/ __/ __| |
|  _| | | |_) | (_) | | | | (_| | (_| (__| |
|_|   |_|_.__/ \___/|_| |_|\__,_|\___\___|_|
                                            
Write a program to calculate n Fibonacci numbers using Parallel Directive. Demonstrate elimination of the race condition using Schedule directive.

 */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int fib(int n){
    int i, j;
    if(n<2) return n;
#pragma omp task shared(i) firstprivate(n)
    i = fib(n - 1);
#pragma omp task shared(j) firstprivate(n)
    j = fib(n - 2);
#pragma omp taskwait
    return i + j;
}

int main(){
    int n = 20;
    double start = omp_get_wtime();
#pragma omp parallel for
    for(int i = 0 ; i < n ; i++){
        int t = omp_get_thread_num();
        printf("Thread: %d fib(%d) = %d\n", t, i, fib(i));
    }
    double end = omp_get_wtime();
    printf("Using schedule time is: %f\n", end-start);
    return 0;
}
