#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct result {
    int sum;
};

double *compute(int begin)
{
    double sum=0;
    int i;
	//print("child:");
    for (i = begin; i < 1000; i+=4) 
	{
        sum+=1/begin;
		printf("1/%d+",begin);
    }
    return sum;
}

int main()
{ 
	double sum,left,right;
    pthread_t worker_tid;
    pthread_create(&worker_tid, NULL, &compute, 3);
	pthread_join(worker_tid, (void **)&result);
	right = result->sum;
	left = compute(1);
	sum = left - right;
	
    printf("sum=%f",begin);
    return 0;
}
