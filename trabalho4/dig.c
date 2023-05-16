#include <stdio.h>

int main(){

	int nr,x,done = 0,cr;

	do{

		printf("Introduza um número com três algarismos: ");
		scanf(" %d",&nr);

		if(nr > 999){
				printf("Erro. Tem mais de três algarismos.\n");
				break;

		}
		else if (nr < 100){
			printf("Erro. Não tem três algarismos.\n");
			break;

		}

		else{
		    for(x=1;x<4;x++){
			
			    if(x == 1 ){
			    	printf("O algarismo das centenas é o ");
			    	cr = nr/100;

		    	}

		    	if(x == 2 ){
		    		printf("O algarismo das dezenas é o ");
		    		cr = nr/10;

		    	}

		    	if(x == 3 ){
		    		printf("O algarismo das unidades é o ");
		    		cr = nr;
    
		    	}
		    	for(cr;cr>10;cr = cr -10){}

		    	switch(cr){
				
		    		case 1 : printf("um\n");
		    		    break;

		    		case 2 : printf("dois\n");
			    	    break;

			    	case 3 : printf("três\n");
			    	    break;
    
			    	case 4 : printf("quatro\n");
			    	    break;

			    	case 5 : printf("cinco\n");
				        break;

			    	case 6 : printf("seis\n");
				      break;

			    	case 7 : printf("sete\n");
			    	    break;

			    	case 8 : printf("oito\n");
			    	    break;

			    	case 9 : printf("nove\n");
			    	    break;

		    	}

		
		}
		done = 1;
		}

	}while(!done);
	
}
