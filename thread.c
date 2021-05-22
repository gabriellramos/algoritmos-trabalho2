#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMERO_DE_THREADS 2

void *numeroCrescente(void *tid){
	int i, limite=500;
	printf ("Thread %d contando numeros em ordem crescente\n", tid);
	for (i=1;i<=limite;i++){
		printf ("%d-%d\t", i, tid);
	}
	printf ("\n");
	pthread_exit(NULL);
}

void *numeroDecrescente(void *tid){
	int i, limite=500;
	printf ("Thread %d contando numeros em ordem decrescente\n", tid );
	for (i=limite;i>0;i--){
		printf ("%d-%d\t", i,tid);
	}
	printf ("\n");
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads1, threads2;
	int i, status;
	
	status = pthread_create(&threads1, NULL, numeroCrescente, (void*)1);
	status = pthread_create(&threads2, NULL, numeroDecrescente, (void*)2);
	
	pthread_join(threads1, NULL);
	//pthread_join(threads2, NULL);
	

	return 0;
}
