#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct result_t {
    int *xxx;
};

void* xuanze(void *begin)//简单选择排序
{//x[100]
	x=(int*)begin;
    int i,j,t,k;
	for(i=0;i<9;i++)
	{
		k=i;
		for(j=i+1;j<10;j++)
			if(x[j]<x[k])
				k=j;
		t=x[i];
		x[i]=x[k];
		x[k]=t;
	}
	return x;
}


int main()
{
	int indata[20]=[11,5 ,13, 6 ,14 ,2 ,19 ,7 ,18 ,0 ,1 ,15, 3, 16, 4, 12, 9 ,17, 8 ,10]
	int *pre=indata,*las=&indata[10];
	int i;
	struct result *result;
	pthread_t worker1,worker2;
	
	
	for(i=0; i<10 ;i++)//show
		printf("%d ",pre[i]);
	printf("\n");
	for(i=0; i<10 ;i++)
		printf("%d ",las[i]);
    printf("\n");
    //result = malloc(sizeof(struct result));
    //result->sum = 3;
    
    pthread_create(&worker1, NULL, xuanze, pre);
	pthread_join(worker1, (void **)&pre);
	pthread_create(&worker2, NULL, xuanze, las);
	pthread_join(worker2, (void **)&las);
	
	for(i=0; i<10 ;i++)//show
		printf("%d ",pre[i]);
	printf("\n");
	for(i=0; i<10 ;i++)
		printf("%d ",las[i]);
   

    return 0;
}
