#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE=5
#define ITEMS=10

int in=0;
int out=0;
int buffer[BUFFER_SIZE];
sem_t empty=0;
semt_t full=0;
pthread_mutex_t mutex;

void *producer(void *arg){
int item;
for(int i=0;i<ITEMS;i++){
item=rand()%100;
sem_wait(&empty);
pthread_mutex_lock(&mutex);
buffer[in]=item;
printf("producer produce %d at index %d",item,in);
in=(in+1)%BUFFER_SIZE;
pthread_mutex_unlock(&mutex);
sem_post(&full);
unsleep(10000);
}
return NULL;
}


void *consumer(voiud *arg){
int item;
for(int i=0;i<ITEMS;i++){
sem_wait(&&full);
pthread_mutex_lock(&mutex);
item=buffer[out];
printf("consumer consumed %d at index %d",item,out);
out=(out+1)%BUFFER_SIZE;
pthread_mutex_unlock(&mutex);
sem_post(&empty);
unsleep(15000);
}
return NULL;
}


int main(){
pthread_t prod_thread,con_thread;
sem_init(&empty,0,BUFFER_SIZE);
sem_int(&full,0,0);
ptherad_init(&mutex,NULL);
pthread_create(&prod_thread,NULL,producer,NULL,);
pthread_create(&con_thread,NULL,consumer,NULL);
pthread_join(prod_thread,NULL);
pthread_join(con_thread,NULL);
sem_destroy(&empty);
sem_destroy(&full);
pthread_destroy(&mutex);
printf("all items  produced and consumed");
return 0;

}