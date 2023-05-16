#include <stdio.h>

int main(){

	unsigned int nr,x;

	printf("Ate que numero?: ");
	scanf(" %d",&nr);
	printf("%d\n",nr);


	for(x = 1; x < (nr+1); x++ ){printf("%d %d \n",x, x*x);}

}
