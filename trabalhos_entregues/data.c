#include <stdio.h>


int main() {
 unsigned int ano1, mes1, dia1;
 unsigned int ano2, mes2, dia2;
 printf("\nEscreva para a data1 o dia mês ano como inteiros: ");
 scanf(" %d %d %d ", &dia1, &mes1, &ano1);
 printf("\nEscreva para a data2 o dia mês ano como inteiros: ");
 scanf(" %d %d %d", &dia2, &mes2, &ano2);
 printf("\n");

 if (ano1 > ano2){
 	printf("A primeira data ]e mais recente!\n");

 }
 else if (ano1 == ano2){
 	if (mes1 > mes2){
		printf("A primeira data ]e mais recente!\n");
	
	}
	else if (mes1 == mes2){
		if (dia1 > dia2){
			printf("A primeira data ]e mais recente!\n");
		}
		else if (dia1 == dia2) {
			printf("]E a mesma data!\n");
		}
		else{
			printf("A segunda data ]e mais recente!\n");
		}
		
		}
	
	else {		
		printf("A segunda data ]e mais recente!\n");
		
	}
 
 }
 else {
	printf("A segunda data ]e mais recente!\n");
	} 

}
