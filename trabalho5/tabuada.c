#include <stdio.h>
#include <stdlib.h>


void tabuada(int nr){int x;for(x = 1; x < 11 ; x++)printf("%d * %d = %d \n", x ,nr , (nr * x));}}

int main(){
	int n;

	printf ("Que tabuada quer (1 a 9)? : ");
	if (scanf (" %d", &n) != 1) { /* Se não leu um elemento */
 		printf ("Leitura do limite inválida\n");
 		exit (1); /* Sai do programa */
 	}
 	if ((n < 1) || (n > 9)) {
 		printf (" Número incorrecto. Tente outra vez\n");
		exit (1);
 	}
 	tabuada (n);
	return 0;
}
