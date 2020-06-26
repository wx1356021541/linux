#include <stdio.h>
#include <unistd.h>
#include <pthread.h>



void* xuanze(void *begin)//简单选择排序
{//x[100]
	int *x;
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
	int indata[20]={11,5 ,13, 6 ,14 ,2 ,19 ,7 ,18 ,0 ,1 ,15, 3, 16, 4, 12, 9 ,17, 8 ,10};
	int *pre=indata,*las=&indata[10];
	int i;
	struct result *result;
	pthread_t worker1,worker2;


	printf("before sort\n");
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

	printf("(after sort)pre:");
	for(i=0; i<10 ;i++)//show
		printf("%d ",pre[i]);
	printf("\n(after sort)las:");
	for(i=0; i<10 ;i++)
		printf("%d ",las[i]);

	int asd;
	int *p=pre,*q=las;
    int xxx[20];
    int *jjj=xxx;
    while(1)
    {
        if(p==&asd&&q==&asd)
        {
            break;
        }
        else if(p==&asd||*p>=*q)
        {
            *jjj=*q;
            //cout<<'q'<<*q<<' ';
            if(q==&las[9])
                q=&asd;
            else
                q++;
            jjj++;
        }
        else if(q==&asd||*p<*q)
        {
            *jjj=*p;
            if(p==&pre[9])
                p=&asd;
            else
                p++;
            jjj++;
        }
    }

	printf("\nanswer:\n");
	for(i=0; i<20 ;i++)
		printf("%d ",xxx[i]);

    return 0;
}
