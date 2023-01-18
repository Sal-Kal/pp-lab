# Part A: OpenMP Program
1. Write a program to sort an array on n elements using both sequential and parallel merge sort(using Section). Record the difference in execution time.
```c
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void merge(int a[], int l, int mid, int h){
    int n1 = mid-l+1;
    int n2 = h-mid;

    int arr1[n1], arr2[n2];
    for(int i=0;i<n1;i++)   arr1[i]=a[l+i];
    for(int i=0;i<n2;i++)   arr2[i]=a[mid+1+i];

    int i=0,j=0,k=1;

    while(i<n1 && j<n2){
        if(arr1[i]<=arr2[j])
            a[k++]=arr1[i++];
        else
            a[k++]=arr2[j++];
    }

    while(i<n1)
        a[k++]=arr1[i++];
    while(j<n2)
        a[k++]=arr2[j++];
    
}

void mergeSortParallel(int a[], int l, int h){
    if(l>=h)
        return;
    int mid=l+(h-l)/2;
    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortParallel(a, l, mid);

        #pragma omp section
        mergeSortParallel(a,mid+1, h);
    }
    merge(a,l,mid,h);
}

void mergeSortSerial(int a[], int l, int h){
    if(l>=h)
        return;
    int mid=l+(h-l)/2;
    mergeSortSerial(a, l, mid);
    mergeSortSerial(a, mid+1, h);
    merge(a,l,mid,h);
}

int main(){
    int *a, i;
    int n = 1e6;
    a = (int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
        a[i]=rand()%100;
    double start = omp_get_wtime();
    mergeSortSerial(a,0,n-1);
    double end = omp_get_wtime();
    double val = end-start;
    printf("Serial : %f\n", val);
    
    start=omp_get_wtime();
    mergeSortParallel(a,0,n-1);
    end=omp_get_wtime();
    val=end-start;
    printf("Parallel : %f\n", val);
    return 0;
}
```
---
2. Estimate the value of pi using: $$\pi=4*\sum_{k=0}^\infty\frac{(-1)^k}{2k+1}$$
Parallelize the code by removing loop carried dependency and record both serial and parallel execution times.
```c
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

#define num_steps 10000000

int main(){
    double pi = 0;
    double start = omp_get_wtime();
    for(int k=0;k<num_steps;k++)
        pi+=pow(-1,k)/(2*k+1);

    pi = 4*pi;
    double end = omp_get_wtime();
    double time = end-start;
    printf("Serial :%f, pi=%lf", time, pi);
// PARALLEL
    pi=0;
    start=omp_get_wtime();
    double thread[8];
    #pragma omp parallel for num_threads(8)
    for(int k=0;k<num_steps;k++){
        int t= omp_get_thread_num();
        thread[t] +=pow(-1,k)/(2*k+1);
    }
    for(int i=0;i<8;i++)
        pi+=thread[i];

    pi=4*pi;
    end=omp_get_wtime();
    time=end-start;
    printf("\nParallel :%f, pi=%lf", time, pi);
    return 0;
}
```
---
3. Write an OpenMP program that divides the Iterations into chunks containing 2 iterations, respectively (OMP_SCHEDULE=static,2). Its input should be the number of iterations, and its output should be which iterations of a parallelized for loop are executed by which thread. For example, if there are two threads and four iterations, the output might be the following:
	a.	Thread 0 : Iterations 0 −− 1
	b.	Thread 1 : Iterations 2 −− 3

```c
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    int iterns,itern[8];
    iterns = 2;
    #pragma omp parallel for schedule(static, 2)
    for(int i=1;i<=iterns;i++){
        int t = omp_get_thread_num();
        itern[t]+=1;
        printf("Thread %d : Iteration %d -- %d\n", t, itern[t], i);
    }
}
```
---
4. Write a program to calculate n Fibonacci numbers using Parallel Directive. Demonstrate elimination of the race condition using Schedule directive.
```c
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int fib(int n){
    int i,j;
    if(n<2) return n;
    #pragma omp task shared(i) firstprivate(n)
    i = fib(n-1);
    #pragma omp task shared(j) firstprivate(n)
    j=fib(n-2);
    #pragma omp taskwait
    return i+j;
}

int main(){
    int n=20;
    double start = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        int t=omp_get_thread_num();
        printf("Thread: %d fib(%d)=%d\n",t, i, fib(i));
    }
    double end = omp_get_wtime();
    printf("using schedule time is : %f\n", end-start);
    return 0;
}
```
---
5. Write a program to find the prime numbers from 1 to n employing parallel for directive. Record both serial and parallel execution times
```c
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<stdbool.h>

bool isprime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0)
            return 0;
    }
    return 1;
}

int main(){
    int i=0,n=100000,x=2,primes[110000];
    double start=omp_get_wtime();
    #pragma omp parallel
    while(i<n){
        if(isprime(x)){
            primes[i]=x;
            #pragma omp atomic
            i++;
        }
        #pragma omp atomic
        x++;
    }
    double end = omp_get_wtime();
    printf("Parallel: %f\n", end-start);

    i=0;x=2;
    start=omp_get_wtime();
    while(i<n){
        if(isprime(x)){
            primes[i]=x;
            i++;
        }
        x++;
    }
    end=omp_get_wtime();
    printf("Serial: %f\n", end-start);
}
```
---
6. Parallel Vector Addition
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n = 1e8;
    int *vector_a=(int *)malloc(sizeof(int)*n);
    int *vector_b=(int *)malloc(sizeof(int)*n);
    int *res_vector=(int *)malloc(sizeof(int)*n);
    int *ser_vector=(int *)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        vector_a[i] = rand() % 10;
        vector_b[i] = rand() % 10;
    }
    double start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        res_vector[i] = vector_a[i] + vector_b[i];
    double end = omp_get_wtime();
    printf("Parallel : %f\n", end - start);

    start = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        ser_vector[i] = vector_a[i] + vector_b[i];
    }
    end = omp_get_wtime();
    printf("Serial : %f", end - start);
    return 0;
}
```
---
7. Write a program calculate the sum of first 100 Numbers. (Using critical directive)
```c
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    int n=1e5;
    long int sum=0;
    #pragma omp parallel for
    for(int i=1;i<=n;i++){
        #pragma omp critical
        sum+=i;
    }
    printf("Sum is %d\n", sum);
}
```
---
# Part B:  MPI programs
1.  Write a MPI program to implement Blocking send and receive functions.
```c
#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char outmsg[100] = "Supppp";
    char inmsg[100];
    MPI_Status stat;
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        MPI_Send(&outmsg, strlen(outmsg), MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&inmsg, strlen(outmsg), MPI_CHAR, 0, 1, MPI_COMM_WORLD, &stat);
        printf("%s\n", inmsg);
        printf("TASK %d, recieved %d char(s) task from %d with tag %d & msg is %s\n", rank, size, stat.MPI_SOURCE, stat.MPI_TAG, inmsg);
    }
    MPI_Finalize();
    return 0;
}
```
---
2. Write a MPI program to demonstrate deadlock and implement a solution to avoid deadlock
```c
#include<stdio.h>
#include<string.h>
#include<mpi.h>
#include<stdlib.h>

int main(){
    int rank, size, tag1=1, tag2=2;
    int out=77, in;
    MPI_Init(NULL, NULL);
    MPI_Status stat;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0){
        MPI_Send(&out, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
        MPI_Recv(&in, 1, MPI_INT, 1, tag2, MPI_COMM_WORLD, &stat);

    }
    else if(rank==1){
        MPI_Recv(&in, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &stat);
        MPI_Send(&out, 1, MPI_INT, 0, tag2, MPI_COMM_WORLD);
    }

    //For deadlock interchange the tags of else if 
    printf("rank %d msg %d with tag %d from task %d\n", rank, in, stat.MPI_TAG, stat.MPI_SOURCE);
    MPI_Finalize();
    return 0;
}
```
---
3. Write a MPI program to implement Vector Addition of two vectors to generate resultant vector using Scatter and gather operation.
```c
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;
    int n=10;
    int a[100], b[100], c[100];
    for(int i=0;i<n;i++){
        a[i] = rand()%10;
        printf("%d ", a[i]);
    }
    printf("\n");
    for(int i=0;i<n;i++){
        b[i] = rand()%10;
        printf("%d ", b[i]);
    }
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int subsize = n/size;
    int *ap = malloc(sizeof(int)*subsize);
    int *bp = malloc(sizeof(int)*subsize);
    int *cp = malloc(sizeof(int)*subsize);

    MPI_Scatter(a, subsize, MPI_INT, ap, subsize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, subsize, MPI_INT, bp, subsize, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0;i<subsize;i++)
        cp[i]=ap[i]+bp[i];

    MPI_Gather(cp, subsize, MPI_INT, c, subsize, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0){
        printf("\nres:\n");
        for(int i=0;i<n;i++)
            printf("%d ", c[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
```
---
4.	Write a MPI program to find factorial of a number using Broadcast and Reduce operation.

```c
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int n, rank, size;
    n=7;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int global;
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int localprod = 1;
    int len= (n/size)+1;
    for(int i=1;i<=len;i++){
        printf("rank %d len:%d i:%d\nn:%d", rank, len, i, n);
        int val = (rank*len)+i;
        printf(" rank: %d val: %d\n", rank, val);
        if(val<=n)
            localprod*=val;
        else break;
    }

    printf("LOCAL PRD: %d\n", localprod);
    MPI_Reduce(&localprod, &global, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    if(rank==0)
        printf("Factorial of %d is %d\n", n, global);
    MPI_Finalize();
}
```
---
5. Write a MPI program to generate all prime numbers till ‘n’ (n being user input).
```c
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int isprime(int x){
    if(x==0) return 0;
    if(x==1) return 0;
    if(x==2) return 1;
    for(int i=2;i*i<=x;i++){
        if(x%i==0)
            return 0;
    }
    return 1;
}

int main(){
    int size, rank;
    int n=179;
    int *globaldata = malloc(n*sizeof(int));
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for(int i=0;i<n;i++)
        globaldata[i]=i+1;
    int itern = (n/size)+1;
    printf("\nrank %d itern %d size %d n %d\n", rank, itern, size, n);
    for(int i=(rank*itern);i<((rank+1)*itern);i++){
        if(i>n) break;
        if(isprime(globaldata[i])){
            printf("%d ", globaldata[i]);
        }
    }
    MPI_Finalize();
    return 0;
}
```
---