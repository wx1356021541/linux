#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 4
int buffer1[CAPACITY];
int buffer2[CAPACITY];
int in;//1
int inend;//1

int beginout;//2
int out;//2


int buffer1_is_empty()
{
    return in == inend;
}

int buffer1_is_full()
{
    return (in + 1) % CAPACITY == inend;
}

int get_item_1()
{
    int item;

    item = buffer1[inend];
    inend = (inend + 1) % CAPACITY;
    return item;
}

void put_item_1(int item)
{
    buffer1[in] = item;
    in = (in + 1) % CAPACITY;
}

int buffer2_is_empty()
{
    return beginout == out;
}

int buffer2_is_full()
{
    return (beginout + 1) % CAPACITY == out;
}

int get_item_2()
{
    int item;

    item = buffer2[out];
    out = (out + 1) % CAPACITY;
    return item;
}

void put_item_2(int item)
{
    buffer2[beginout] = item;
    beginout = (beginout + 1) % CAPACITY;
}

////////////
pthread_mutex_t mutex1;
pthread_cond_t wait_empty_buffer1;
pthread_cond_t wait_full_buffer1;
pthread_mutex_t mutex2;
pthread_cond_t wait_empty_buffer2;
pthread_cond_t wait_full_buffer2;
#define ITEM_COUNT (CAPACITY * 2)
/*
void *consume1(void *arg)///////////
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex1);
        while (buffer1_is_empty())
            pthread_cond_wait(&wait_full_buffer1, &mutex1);

        item = get_item_1();
        printf("    consume1 item: %c\n", item);

        pthread_cond_signal(&wait_empty_buffer1);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}
///////////////
void *produce2(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex2);
        while (buffer2_is_full())
            pthread_cond_wait(&wait_empty_buffer2, &mutex2);

        item = 'a' + i;
        put_item_2(item);
        printf("produce2 item: %c\n", item);

        pthread_cond_signal(&wait_full_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}*/
void *change(void *arg)
{
	int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex1);
        while (buffer1_is_empty())
            pthread_cond_wait(&wait_full_buffer1, &mutex1);

        item = get_item_1();
        printf("    get and put item: %c -> %c\n", item,item-32);

        pthread_cond_signal(&wait_empty_buffer1);
        pthread_mutex_unlock(&mutex1);

		pthread_mutex_lock(&mutex2);
        while (buffer2_is_full())
            pthread_cond_wait(&wait_empty_buffer2, &mutex2);

        item -= 32;
        put_item_2(item);
//        printf("daxie item: %c\n", item);

        pthread_cond_signal(&wait_full_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}


void *consume2(void *arg)//out
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex2);
        while (buffer2_is_empty())
            pthread_cond_wait(&wait_full_buffer2, &mutex2);

        item = get_item_2();
        printf("        consume2 item: %c\n", item);

        pthread_cond_signal(&wait_empty_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void *produce1(void *arg)//in
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex1);
        while (buffer1_is_full())
            pthread_cond_wait(&wait_empty_buffer1, &mutex1);

        item = 'a' + i;
        put_item_1(item);
        printf("produce1 item: %c\n", item);

        pthread_cond_signal(&wait_full_buffer1);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}
//////////

int main()
{
    pthread_t consumer_tid1,consumer_tid2;

    pthread_mutex_init(&mutex1, NULL);
    pthread_cond_init(&wait_empty_buffer1, NULL);
    pthread_cond_init(&wait_full_buffer1, NULL);
	pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&wait_empty_buffer2, NULL);
    pthread_cond_init(&wait_full_buffer2, NULL);
	///////
    pthread_create(&consumer_tid1, NULL, consume2, NULL);
	pthread_create(&consumer_tid2, NULL, change, NULL);
    produce1(NULL);
    pthread_join(consumer_tid1, NULL);
    pthread_join(consumer_tid2, NULL);
    return 0;
}
