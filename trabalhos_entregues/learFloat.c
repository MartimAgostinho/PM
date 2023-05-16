#include <stdio.h>
#include <stdlib.h>

int main()
{

	float fnr = 0, lp = 100;
	char nr;
	int sucesso=0;

	printf("Insira os numeros\n");

	while (!sucesso){
		
		scanf(" %c",&nr);
		nr = nr - '0';

		if ((nr <0 || nr > 9) && (nr != -4)){
		
			printf("Precisa ser um numero entre 0 e 9\n");
			exit(1);
		}

		if (nr != -4){

			fnr = fnr + (float)lp*nr;
			lp = lp/10;
		}

		if (lp <= 0.001){
			printf("O numero ]e %.3e ou na forma tradicional %0.2f\n",fnr,fnr);
			sucesso = 1;
		}
	
	}
	return 0;
}
