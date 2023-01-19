/*
  ____      _ _   _           _   ____  _               _   _           
 / ___|_ __(_) |_(_) ___ __ _| | |  _ \(_)_ __ ___  ___| |_(_)_   _____ 
| |   | '__| | __| |/ __/ _` | | | | | | | '__/ _ \/ __| __| \ \ / / _ \
| |___| |  | | |_| | (_| (_| | | | |_| | | | |  __/ (__| |_| |\ V /  __/
 \____|_|  |_|\__|_|\___\__,_|_| |____/|_|_|  \___|\___|\__|_| \_/ \___|

Write a program to calculate the sum of first 100 numbers using critical directive.
 */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    int n = 1e5, i;
    long int sum = 0;
#pragma omp parallel for
    for(i = 0 ; i < n ; i++){
#pragma omp critical
        sum += i;
    }
    printf("The Sum is %ld", sum);
}
