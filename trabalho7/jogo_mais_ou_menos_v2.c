#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randm(int min,int max){ return (time(NULL) % max) + min; }

void clear(){

	system("clear");
	printf("     ██╗ ██████╗  ██████╗  ██████╗        ██████╗  ██████╗        ███████╗ ██████╗ ██████╗ ███████╗       ███████╗    ██████╗ ███████╗███████╗ ██████╗███████╗\n");
	printf("     ██║██╔═══██╗██╔════╝ ██╔═══██╗       ██╔══██╗██╔═══██╗       ██╔════╝██╔═══██╗██╔══██╗██╔════╝       ██╔════╝    ██╔══██╗██╔════╝██╔════╝██╔════╝██╔════╝\n");
	printf("     ██║██║   ██║██║  ███╗██║   ██║       ██║  ██║██║   ██║       ███████╗██║   ██║██████╔╝█████╗         █████╗      ██║  ██║█████╗  ███████╗██║     █████╗  \n");
	printf("██   ██║██║   ██║██║   ██║██║   ██║       ██║  ██║██║   ██║       ╚════██║██║   ██║██╔══██╗██╔══╝         ██╔══╝      ██║  ██║██╔══╝  ╚════██║██║     ██╔══╝  \n");
	printf("╚█████╔╝╚██████╔╝╚██████╔╝╚██████╔╝       ██████╔╝╚██████╔╝       ███████║╚██████╔╝██████╔╝███████╗       ███████╗    ██████╔╝███████╗███████║╚██████╗███████╗\n");
	printf(" ╚════╝  ╚═════╝  ╚═════╝  ╚═════╝        ╚═════╝  ╚═════╝        ╚══════╝ ╚═════╝ ╚═════╝ ╚══════╝       ╚══════╝    ╚═════╝ ╚══════╝╚══════╝ ╚═════╝╚══════╝\n\n\n");


}

void nivel(int opc,int *lvl){
	
	int nivel;
	opc--;

	if(opc){
		do{
			printf("\n\n Introduza o nivel(1 a 3): ");
			scanf(" %d",&nivel);
			printf("\n");

		}while( (nivel < 1) || (nivel > 3) );
	}
	else{nivel = randm(1,3);}

	*lvl = nivel;
}

void tentativas(int opc,int *tent){

	int tentativas;
	opc--;

	if(opc){

		printf("Ha 3 valores para o numero de tentativas\n");
		printf("Tentativas 1: 10\nTentativas 2: 15\nTentativas 3: 20\n");
		printf("Escolha um valor, de 1 a 3 correspondente ao numero de tentativas: ");
		scanf(" %d",&tentativas);
		printf("\n");

		while((tentativas < 1) || (tentativas > 3)){
			printf("Erro na introducao de dados\n");
			printf("Escolha um numero de 1 a 3: ");
			scanf(" %d",&tentativas);
			printf("\n");
		}
	}
	else{tentativas = randm(1,3);}

	switch(tentativas){

		case 1 : tentativas = 10;
			break;

		case 2 : tentativas = 15;
			break;

		case 3 : tentativas = 20;
			break;
	}

	*tent = tentativas;
}

void nr_misterio(int opc,int nivel,int *nr_mist){

	int max,nr;
	opc--;

	switch(nivel){

		case 1 : max = 100;
			break;

		case 2 : max = 1000;
			break;

		case 3 : max = 10000;
			break;

	}

	if(opc){

		printf("Escolhe um numero de 1 a %d: ",max);
		scanf(" %d",&nr);
		printf("\n");
		while((nr < 1) || (nr > max)){
			printf("Erro na introducao de dados\n");
			printf("Escolha um numero de 1 a %d: ",max);
			scanf(" %d",&nr);
			printf("\n");
		}
	}
	else{nr = randm(1,max);}

	*nr_mist = nr;
}

int jogo(int tentativas,int nivel,int nr_mist){

	int guess,win=0,t=0,max;
	char again;

	switch(nivel){

		case 1 : max = 100;
			break;

		case 2 : max = 1000;
			break;

		case 3 : max = 10000;
			break;

	}

	clear();

	printf("\nNivel: %d\n",nivel);
	printf("Tentativas: %d\n",tentativas);
	printf("O numero misterio esta entre 1 e %d",max);
	
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

	printf("\nQuer jogar outra vez (s ou n): ");
	scanf(" %c",&again);

	if(again == 's'){return 1;}
	
	else{printf("\nAdeus.\n");return 0;}

}

void menu(){

	int opc,lvl,tent,nr_mist;

	do{
		clear();
		printf("Valores por sorteio(1) ou manuais(2): ");
		scanf(" %d",&opc);

		while( (opc!=1 ) && (opc!=2) ){
	
			printf("\nErro na introdução de dados.\n");
			printf("\nValores por sorteio (1) ou manuais (2): ");
			scanf(" %d",&opc);
		}
		printf("\n");
		nivel(opc,&lvl);
		tentativas(opc,&tent);
		nr_misterio(opc,lvl,&nr_mist);

	}while(jogo(tent,lvl,nr_mist));

}

int main(){
	menu();
	return 0;
}
