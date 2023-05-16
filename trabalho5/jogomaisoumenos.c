#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int randm(int max,int min){

	srand(time(NULL));
	return (rand() % max ) + min;

}
int nmist(int nivel){

	switch(nivel){

	case 1 :
		nr_mist = randm(100,1);
		printf("Estamos a jogar com o nível 1 (1 a 100) e com um máximo de tentativas ");
		break;

	case 2:
		nr_mist = randm(1000,1);
		printf("Estamos a jogar com o nível 2 (1 a 1000) e com um máximo de tentativas ");
		break;


	case 3:
		nr_mist = randm(10000,1);
		printf("Estamos a jogar com o nível 3 (1 a 10000) e com um máximo de tentativas ");
		break;

	}
	return nr_mist;

}

int tentativas(int t){

	

}

int jogo(int tentativas,int nivel){

	int nr_mist,guess,win=0,t=0;
	char again;

	nr_mist = nmist(nivel);
	
	do{
		printf("\nDiga um número: ");
		scanf(" %d",&guess);
		
		if(guess < nr_mist){
		
			printf("\nO numero mistério está a cima.");
			t += 1;
		
		}
		else if (guess > nr_mist){
		
			printf("\nO numero mistério está a baixo.");
			t += 1;

		}
		else{
		
			win=1;
			break;

		}



	}while(tentativas > t);

	if(win){
	
		printf("\nParabéns!\nAcertou em %d tentativas",t);

	
	}
	else{printf("\nPerdeste!");}

	printf("\nQuer jogar outra vez (s ou n): ",&again);
	scanf(" %c",&again);

	if(again == 's'){return 1;}
	
	else{printf("\nAdeus.\n");return 0;}

}


void menu(){

	int opc,done=0,nivel;

do{
	system("clear");


	printf("/********* JOGO DO SOBE E DESCE **************/\n");
	
	printf("\nValores por sorteio (1) ou manuais (2): ");
	scanf(" %d",&opc);

	while( (opc!=1 ) && (opc!=2) ){
	
		printf("\nErro na introdução de dados.\n");
		printf("\nValores por sorteio (1) ou manuais (2): ");
		scanf(" %d",&opc);
	}

	if(opc==1){
		
		jogo(tentativas(),randm(1,3));
	}

	else{
		do{
			printf("\n\n Introduza o nivel(1 a 3): ");
			scanf(" %d",&nivel);

		}while( (nivel<1) || (nivel > 3) );
	}
}while(jogo(nivel));
	


}

int main(){
	/*
	int opc,done=0,nivel;

	system("clear");


	printf("|********* JOGO DO SOBE E DESCE *************|\n");
	
	printf("\nValores por sorteio (1) ou manuais (2): ");
	scanf(" %d",&opc);

	while( (opc!=1 ) && (opc!=2) ){
	
		printf("\nErro na introdução de dados.\n");
		printf("\nValores por sorteio (1) ou manuais (2): ");
		scanf(" %d",&opc);
	}

	if(opc==1){jogo(randm(3,1));}

	else{
		do{
			printf("\n\n Introduza o nivel(1 a 3): ");
			scanf(" %d",&nivel);

		}while( (nivel<1) || (nivel > 3) );

		jogo(nivel);
	}
	*/
	menu();
	return 0;
}
