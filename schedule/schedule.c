//Demonstrate schedule with various parameter/s combinations
#include<omp.h>
#include<stdio.h>
int main()
{
    printf("static scheduling\n");
    #pragma omp parallel for schedule(static,3)
    for(int i=0;i<10;i++)
        printf("Thread %d is running numbers %d\n",omp_get_thread_num(),i);
    printf("dynamic scheduling\n");
    #pragma omp parallel for schedule(dynamic,4)
    for(int i=0;i<10;i++)
        printf("Thread %d is running numbers %d\n",omp_get_thread_num(),i);
    printf("guided scheduling\n");
    #pragma omp parallel for schedule(guided,4)
    for(int i=0;i<10;i++)
        printf("Thread %d is running numbers %d\n",omp_get_thread_num(),i);
    printf("runtime scheduling\n");
    #pragma omp parallel for schedule(runtime)
    for(int i=0;i<10;i++)
        printf("Thread %d is running numbers %d\n",omp_get_thread_num(),i);
    return 0;
}