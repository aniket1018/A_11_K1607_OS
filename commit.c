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
