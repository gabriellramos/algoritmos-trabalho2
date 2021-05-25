#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	char p[3] = "p";
	int i = 1;
	char aux[2];
	sprintf(aux,"%d", 1);
	printf ("oi %s", strcat(p, aux));
}
