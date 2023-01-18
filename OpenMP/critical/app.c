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
