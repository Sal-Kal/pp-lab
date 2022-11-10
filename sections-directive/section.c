//Write an OPENMP program to implement section directive
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    #pragma omp parallel
    {
        #pragma omp sections
        {
            printf("This is from thread %d\n",omp_get_thread_num());
        }
        #pragma omp sections
        {
            printf("This is from thread %d\n",omp_get_thread_num());
        }
    }
}