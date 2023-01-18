/*
 ____       _              _       _ _             
/ ___|  ___| |__   ___  __| |_   _| (_)_ __   __ _ 
\___ \ / __| '_ \ / _ \/ _` | | | | | | '_ \ / _` |
 ___) | (__| | | |  __/ (_| | |_| | | | | | | (_| |
|____/ \___|_| |_|\___|\__,_|\__,_|_|_|_| |_|\__, |
                                             |___/ 

Write an OpemMP program that divides the iterations into chunks containing 2 iterations, respectively (OMP_SCHEDULE = static, 2). Its input should be the number of iterations, and its output should be which iterations of a paralellized for loop are executed by which thread.

 */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    int iterns, itern[8];
    iterns = 2;
#pragma omp parallel for schedule(static, 2)
    for(int i = 1 ; i <= iterns ; i++){
        int t = omp_get_thread_num();
        itern[t] += 1;
        printf("Thread %d: Iteration %d -- %d \n", t, itern[t], i);
    }
}
