#include <stdio.h>
int main ()
{
const int nr=3;

short int  val1, val2, val3;

short int total;
short int media;
printf("introduza os tres valores: \n");
scanf(" %hd",&val1);
scanf(" %hd",&val2);
scanf(" %hd",&val3);

total = val1+val2+val3;
media = total%nr;

printf("\nA media ds numeros %hd %hd %hd e %d\n ", val1,val2,val3,media);


	}
