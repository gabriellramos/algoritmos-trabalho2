#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int M[3][3];

void *inverteLinha1();
void *inverteLinha2();
void *inverteLinha3();
void recebeMatriz();
void imprimeMatriz();

int main(){
	pthread_t thread1, thread2, thread3;
	
	int i, status;
	
	recebeMatriz(M);
	
	pthread_create(&thread1, NULL, inverteLinha1,(void*)0);
	pthread_create(&thread2, NULL, inverteLinha2, (void*)0);
	pthread_create(&thread3, NULL, inverteLinha3, (void*)0);
	

	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	imprimeMatriz(M);
	
	return 0;
}

void *inverteLinha1(){
	int i, aux, j=2, meio=j/2;

	for (i=0; i<meio; i++, j--){
		aux=M[0][i];
		M[0][i] = M[0][j];
		M[0][j] = aux;
	}
	
}

void *inverteLinha2(){
	int i, aux, j=2, meio=j/2;
	
	for (i=0; i<meio; i++, j--){
		aux=M[1][i];
		M[1][i] = M[1][j];
		M[1][j] = aux;
	}
}

void *inverteLinha3(){
	int i, aux, j=2, meio=j/2;

	for (i=0; i<meio; i++, j--){
		aux=M[2][i];
		M[2][i] = M[2][j];
		M[2][j] = aux;
	}
}

void recebeMatriz(){
	FILE *file = fopen("thread2.txt","r");
	int i,j;
	for (i=0;i<3;i++){
		for (j=0;j<3;j++){
			fscanf(file,"%d ",&M[i][j]);
		}
	}
}

void imprimeMatriz(){
	int i, j;
	for (i=0;i<3;i++){
		for(j=0;j<3;j++)
			printf ("%2d", M[i][j]);
		printf ("\n");
	}
}
