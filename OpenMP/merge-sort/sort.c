/* 
 __  __                       ____             _   
|  \/  | ___ _ __ __ _  ___  / ___|  ___  _ __| |_ 
| |\/| |/ _ \ '__/ _` |/ _ \ \___ \ / _ \| '__| __|
| |  | |  __/ | | (_| |  __/  ___) | (_) | |  | |_ 
|_|  |_|\___|_|  \__, |\___| |____/ \___/|_|   \__|
                 |___/                             

Write a program to sort an array of n elements using both sequential and parallel merge sort(using Section). Record the difference in execution time

*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int a[], int l, int mid, int h){
    int n1 = mid - l + 1;
    int n2 = h - mid;

    int arr1[n1], arr2[n2];

    for(int i = 0 ; i < n1 ; i++) arr1[i] = a[l + i];
    for(int i = 0 ; i < n1 ; i++) arr2[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = 1;
    while(i < n1 && j < n2){
        if(arr1[i] <= arr2[j])
            a[k++] = arr1[i++];
        else
            a[k++] = arr2[j++];
    }
    while(i < n1)
        a[k++] = arr1[i++];
    while(j < n2)
        a[k++] = arr2[j++];
}

void mergeSortParallel(int a[], int l, int h){
    if(l>=h)
        return;
    int mid = l + (h - l) / 2;
#pragma omp parallel sections
    {
#pragma omp section
        mergeSortParallel(a, l, mid);
#pragma omp section
        mergeSortParallel(a, mid+1, h);
    }
    merge(a, l, mid, h);
}

void mergeSortSerial(int a[], int l, int h){
    if(l>=h)
        return;
    int mid = l + (h - l) / 2;
    mergeSortSerial(a, l, mid);
    mergeSortSerial(a, mid+1, h);
    merge(a, l, mid, h);
}

int main(){
    int *a, i;
    int n = 1e6;
    a = (int*)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
        a[i] = rand()%100;
    double start = omp_get_wtime();
    mergeSortParallel(a, 0, n-1);
    double end =  omp_get_wtime();
    double val = end - start;
    printf("Parallel Execution Time: %f \n", val);

    start = omp_get_wtime();
    mergeSortSerial(a, 0, n-1);
    end = omp_get_wtime();
    val = end - start;
    printf("Serial Execution Time: %f \n", val);
}
