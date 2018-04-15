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

int main()
{
	int i;
	sem_init(&buferMut,0,1);
	sem_init(&full,0,0);

    printf("-------------------------------------------Producer Consumer program-------------------------------------------\n");
	printf("\nNumber of Producers : ");
	scanf("%d", &productnum);
	ProduCer = (pthread_t*) malloc(productnum*sizeof(pthread_t));
	printf("---------------------------------------------------------------------------------------");
	
	printf("\nNumber of Consumers : ");
	scanf("%d", &consumernum);
	ConsuMer = (pthread_t*) malloc(consumernum*sizeof(pthread_t));
	printf("---------------------------------------------------------------------------------------");
	
	printf("\nBlock size :");
	scanf("%d", &arraylen);
	array = (int*) malloc(arraylen * sizeof(int));
	printf("---------------------------------------------------------------------------------------");
	
	sem_init(&empty, 0, arraylen);
    int fault;

	for(i = 0;i < productnum; i++){
	fault = pthread_create(ProduCer + i, NULL, &Producer, NULL);
	if(fault != 0){
	printf("\nSome problem in creating producer %d: %s", i + 1, strerror(fault));
	}else{
	printf("\nProducer created successfully %d", i + 1);
	}
	}

	for(i = 0; i < consumernum; i++){
	fault = pthread_create(ConsuMer + i, NULL, &Consumer, NULL);
	if(fault != 0){
	printf("\nProblem in creating consumer no. %d it cannot be Created : %s", i + 1, strerror(fault));
	}else{
	printf("\nconsumer created successfully %d", i + 1);
	}
	}

	for(i=0;i<productnum;i++){
	pthread_join(*(ProduCer+i),NULL);
	}
	for(i=0;i<consumernum;i++){
	pthread_join(*(ConsuMer+i),NULL);
	}


	return 0;
}

