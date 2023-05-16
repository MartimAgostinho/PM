#include <stdio.h>

int main(){


	int n,j,i,esp,estrelas = 1;

	scanf("%d",&n);
	esp = n;

	for(i = 0 ; i < n ; i++){
	
		for(j = 0; j < esp; j++){printf(" ");}
		esp--;
		for(j = 0; j < estrelas; j++){printf("*");}
		estrelas = estrelas + 2;
		printf("\n");

	}

	return 0;
}
