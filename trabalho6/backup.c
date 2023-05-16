#include <stdio.h>
#include <stdlib.h>

#define MxWordL 81
#define MxWord 10
#define MxTxtL 8000

int count_words(char str[MxTxtL]){ 

	int i = 0,n = 0;

	if(str[0] == '\0'){return 0;}

	n = 1;

	while(str[i] != '\0'){
	
		if( (str[i] == ' ') && (str[i-1] != ' ') ){n++;}
		i++;
	}
	
	if (str[0] == ' '){n--;}
	
	return n;
}

void ler_palavras(char str[MxWord][MxWordL],int nw){

	int i,j = 0;

	for(i = 0; i < nw; i++){
	
		if((str[i][j] = getchar() ) != '\n'){ //enquanto nao for um enter vai adicionar a palavra ao vetor i = nr de palavras e j = nr de caracteres de cada palavra
			i--; 
			j++; 
		}	
		else{
			str[i][j] = '\0'; // para nao ter \n no fim de cada linha
			j = 0;
		}
	}
}

int comparar_str(char str1[MxWordL],char str2[MxWordl]){

	int vl,i;

	if((str1[0] == '\0') || (str2[0] == '\0')){
		
		return 0;
		printf("\nERRO compara_str\n");
	}

	for(i = 0;str1[i] != '\0';i++){
	
		if(str1[i] != str2[i]){return 0;}
	
	}
	return 1;

}

void dividir_texto(char text[MxTxtL],char word_txt[MxWord][MxWordL]){

	int i,j;

	for(i = 0;){}

}

void trocar(char og[MxWord][MxWordL],char new[MxWord][MxWordL],char text[MxTxtL]){

	char word_text[MxWord][MxWordL] = {};

	//primeiro ver se as palavras existem todas no texto 
	i = 0;
	while(og[i][0] != '\0'){
		
		if( !(comparar_str(og[i][] , word_text[i][])) ){ exit(1); }
		i++;
	}
	
	//encontrar as palavras no texto 
	//substituilas 


}

int main(){

	char text[MxTxtL] = {" Esta é uma longa string de caracteres"}, og_word[MxWord][MxWordL] = {},new_word[MxWord][MxWordL] = {};
	int nwords,nr_wrd_og = 7;

	system("clear");
	printf("Texto inicial\n%s\n\n",text);
	printf("Quantas palavras tem a lista de substituicao?\n");

	if((scanf("%d",&nwords) < 0) || (nwords > nr_wrd_og)){ exit(1); }
	
	printf("Palavras a desaparecer: ");
	ler_palavras(og_word,nwords);

	printf("Palavras a colocar ");
	ler_palavras(new_word,nwords);

	trocar(og_word,new_word,text);

	printf("N: %d\n",count_words(text));


}
