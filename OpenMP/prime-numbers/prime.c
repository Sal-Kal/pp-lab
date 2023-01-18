/*
 ____       _                  _   _                 _                   
|  _ \ _ __(_)_ __ ___   ___  | \ | |_   _ _ __ ___ | |__   ___ _ __ ___ 
| |_) | '__| | '_ ` _ \ / _ \ |  \| | | | | '_ ` _ \| '_ \ / _ \ '__/ __|
|  __/| |  | | | | | | |  __/ | |\  | |_| | | | | | | |_) |  __/ |  \__ \
|_|   |_|  |_|_| |_| |_|\___| |_| \_|\__,_|_| |_| |_|_.__/ \___|_|  |___/
                                                                         
Write a program to find the prime numbers from 1 to n employing parallel for directive. Record both serial and parallel execution times.
 */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<stdbool.h>

bool isprime(int n){
    for(int i = 2 ; i*i <= n ; i++){
        if(n % i == 0)
            return 0;
    }
    return 1;
}

int main(){
    int i = 0, n = 100000, x = 2, primes[110000];
    double start = omp_get_wtime();
#pragma omp parallel
    while(i < n){
        if(isprime(x)){
            primes[i] = x;
#pragma omp atomic
            i++;
        }
#pragma omp atomic
        x++;
    }
    double end = omp_get_wtime();
    printf("Parallel Execution Time: %f \n", end-start);

    i = 0, x = 2;
    start = omp_get_wtime();
    while(i < n){
        if(isprime(x)){
            primes[i] = x;
            i++;
        }
        x++;
    }
    end = omp_get_wtime();
    printf("Serial Execution Time: %f \n", end - start);
}
