#include<stdio.h>

int main() 
{

	int dias1, horas1, min1, seg1, dias2, horas2, min2, seg2,dt;

	printf("Introduza o tempo no.1 (dia)d (hora)h (minuto)m (segundo)s: ");
	scanf(" %dd %dh %dm %ds", &dias1,&horas1,&min1,&seg1);

	printf("\nIntroduza o tempo no.2 (dia)d (hora)h (minuto)m (segundo)s: ");
	scanf(" %dd %dh %dm %ds", &dias2,&horas2,&min2,&seg2);
	
	dt	= ((dias2-dias1)*86400)+((horas2-horas1)*3600)+((min2-min1)*60)+(seg2-seg1);
	dias1	= dt/86400;
	horas1	= (dt-(dias1*86400))/3600;
	min1	= (dt-((dias1*86400)+(horas1*3600)))/60;
	seg1	= (dt-((dias1*86400)+(min1*60)+(horas1*3600)));

	printf("\nA diferença entre os dois tempos é de %d segundos = %dd %dh %dm %ds\n",dt ,dias1,horas1,min1,seg1);


return 0;
}
