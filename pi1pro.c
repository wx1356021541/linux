#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct result {
    double sum;
};

void *compute(void *begin)
{
    double sum=0;
    double q=0;
    double i;
    struct result *result;
    result=(struct result*)begin;
	//print("child:");
    for (i = result->sum; i < 100000; i+=4)
	{

        sum+=1/i;
		//printf("%f-",sum);
    }
    result->sum = sum;
    return result;
}

int main()
{
	double sum,left,right;
    double i;
    struct result *result;
    result = malloc(sizeof(struct result));
    result->sum = 3;
    pthread_t worker_tid;
    pthread_create(&worker_tid, NULL, compute, result);
	pthread_join(worker_tid, (void **)&result);
	right = result->sum;

    left = 0;
    for (i = 1; i < 100000; i+=4)
	{
        left+=1/i;
		//printf("%f+",left);
    }
	sum = (left - right)*4;

    printf("pi = (%f-%f)*4 = %f",left,right,sum);
    return 0;
}
