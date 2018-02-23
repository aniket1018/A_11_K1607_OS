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
