#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE=5
#define ITEMS=10

int in=0; //index where producer produces next item
int out=0; //index where consumer consumes next item
int buffer[BUFFER_SIZE];
sem_t empty=0; //counts empty slots
semt_t full=0; //counts full slots
pthread_mutex_t mutex; //ensures mutual exclusion

void *producer(void *arg){
int item;
for(int i=0;i<ITEMS;i++){
item=rand()%100; //produces random item
sem_wait(&empty); //waits if the buffer is empty
pthread_mutex_lock(&mutex); //enters ans locks 
buffer[in]=item; //add to the buffer
printf("producer produce %d at index %d",item,in);
in=(in+1)%BUFFER_SIZE; //moves index circularly
pthread_mutex_unlock(&mutex); //unlocks
sem_post(&full); //signal item available
unsleep(10000);
}
return NULL;
}


void *consumer(voiud *arg){
int item;
for(int i=0;i<ITEMS;i++){
sem_wait(&&full); //waits if the buffer is empty
pthread_mutex_lock(&mutex); // goes inside and locks
item=buffer[out]; //removes from buffer
printf("consumer consumed %d at index %d",item,out);
out=(out+1)%BUFFER_SIZE;
pthread_mutex_unlock(&mutex); //unlocks
sem_post(&empty); ///signals empty
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
