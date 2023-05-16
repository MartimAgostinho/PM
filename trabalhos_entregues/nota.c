#include <stdio.h>
#include <stdlib.h>

int main()
{

	unsigned int nota_teorica= 0, nota_pratica= 0, faltas= 0;
 	float media; /* média final */
 	unsigned int nota_final; /* nota final */
 	printf("Cálculo da nota final a PM\n\n");
 	printf("Introduza os seguintes dados:\n");
 	printf("\tNúmero de faltas nos trabalhos práticos: ");
 	scanf("%d", &faltas);
 	printf("\tNota dos trabalhos práticos: ");
 	scanf(" %d", &nota_pratica);
	printf("\tNota dos testes e exames: ");
	scanf(" %d", &nota_teorica);
	
	if (faltas > 3) {
		printf("Reprovou à disciplina por faltas\n");
		media = 0;
		exit(1);

 	} else if (faltas == 2 && nota_pratica > 14) {
		media = 14;
	

	}
	else if (faltas == 3 && nota_pratica > 12){
		media = 12;
	}

	
	media= 0.5*nota_pratica + 0.5*nota_teorica;
	nota_final= (int)(media+0.5);

	if (media >= 9.5){

		printf("Aprovado com a nota final de %d valores (%.1f)\n",nota_final, media); /* Escreve só 1 casa decimal */
	}
	else{
		printf("Reprovado\n");

	}
}
