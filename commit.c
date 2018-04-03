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
}
