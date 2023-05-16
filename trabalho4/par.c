#include<stdio.h>

int main(){


	unsigned int ult,x;

	printf("Numeros par ate que numero?: ");
	scanf(" %d",&ult);
	printf("\n");

	for(x=1;x<(ult+1);x++){
	
		if(x%2== 0){printf("%d \n",x);}
	
	}

}
