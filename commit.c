
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

