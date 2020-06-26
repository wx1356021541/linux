#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define NUMBER 1000
struct result {
    double sum;
};

void *compute(void *begin)
{
    double sum=0;
    //double q=0;
    //double i;
    struct result *result;
    result = malloc(sizeof(struct result));
    result=(struct result*)begin;
	//print("child:");
    sum = 1/result->sum - 1/(result->sum + 2);
    result->sum = sum;
    return result;
}

int main()
{
	double sum=0,left,right;
    int i;
    struct result *result;
    pthread_t worker_tid[NUMBER];

    for(i=1 ; i < NUMBER ; i++)
    {
        result = malloc(sizeof(struct result));
        result->sum =(double)( 4 * i - 3);
        pthread_create(&worker_tid[i], NULL, compute, result);
    }

    for(i=1 ; i < NUMBER ; i++)
    {
	    pthread_join(worker_tid[i], (void **)&result);
	    sum += result->sum;
        free(result);
    }
    printf("pi = %f*4 = %f",sum,4*sum);
    return 0;
}
