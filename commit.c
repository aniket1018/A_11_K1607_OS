#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t buferMut,empty,full;
int *array,arraypos=-1,productnum,consumernum,arraylen;
pthread_t *ProduCer,*ConsuMer;

void Cons(int p,pthread_t self){
	int i = 0;
	while( !pthread_equal(*(ConsuMer + i),self) && i < consumernum ){
	i++;
	}

	printf("\nBlock:");
	for(i = 0; i <= arraypos; ++i)
	printf("%d ",*(array + i));
	printf("\nThe Consumer no. %d consumed %d \nCurrent block length: %d\n",i + 1, p, arraypos);
	printf("---------------------------------------------------------------------------------------");

}

int Prod(pthread_t self){
	int i = 0;
	int a = 1 + rand()%40;
	while( !pthread_equal(*(ProduCer + i),self) && i < productnum ){
	i++;
	}
	printf("\nThe producer no. %d produced %d", i + 1, a);
	return a;
}

void* Consumer(){
	int w;
	while(1){
	sem_wait(&full);
	sem_wait(&buferMut);
	w = *(array + arraypos);
	Cons(w, pthread_self());
	--arraypos;
	sem_post(&buferMut);
	sem_post(&empty);
	sleep(1 + rand()%3);
	}

	return NULL;
}

void* Producer(){
	while(1){
	int v = Prod(pthread_self());
	sem_wait(&empty);
	sem_wait(&buferMut);
	++arraypos; //critical section
	*(array + arraypos) = v;
	sem_post(&buferMut);
	sem_post(&full);
	sleep(1 + rand()%3);
	}
	return NULL;
}

