#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	unsigned int x,nr;

	srand (time(NULL));

	for(x=0;x<19;x++){

		nr =  (rand() % 3)+1;
		printf(" %d \n",nr);
		sleep(1);
	
	}

}
