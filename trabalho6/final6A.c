#include <stdio.h>
#include <stdlib.h>

#define MxWordL 81
#define MxWord 10
#define MxTxtL 8000

void printa(char st[MxWord][MxWordL]){
	int i,j;


	for(j=0;st[j][0] != '\0';j++){

		for(i = 0;st[j][i] != '\0'; i++){ printf("%c",st[j][i]); }
		printf("\n");
	}
	printf("\n");

}

int count_words(char str[MxTxtL]){ 

	int i = 0,n = 0;

	if(str[0] == '\0'){ return 0; }

	n = 1;

	while(str[i] != '\0'){
	
		if( (str[i] == ' ') && (str[i-1] != ' ') ){ n++; }
		i++;
	}
	
	if (str[0] == ' '){ n--; }
	
	return n;
}

void ler_palavras(char str[MxWord][MxWordL],int nw){

	int i,j = 0;

	fflush(stdin);

	for(i = 0; i < nw; i++){
	
		if(( str[i][j] = getchar() ) != '\n'){ //enquanto nao for um enter vai adicionar a palavra ao vetor i = nr de palavras e j = nr de caracteres de cada palavra
			i--; 
			j++; 
		}	
		else{
			str[i][j] = '\0'; // para nao ter \n no fim de cada linha
			j = 0;
		}
	}
}


int comparar_str(char str1[MxWordL],char str2[MxWordL]){

	int i;

	if((str1[0] == '\0') || (str2[0] == '\0')){
		
		printf("\nERRO compara_str\n");
		return 0;

	}

	for(i = 0;str1[i] != '\0';i++){
	
		if(str1[i] != str2[i]){return 0;}
	
	}
	return 1;

}


void dividir_texto(char str[MxTxtL],char word_txt[MxWord][MxWordL]){

	int i = 0 ,j = 0 , k = 0;

	while(str[i] != '\0'){
	
		if( str[i] == ' '){
			j++;
			k = 0;
		}

		else{ 
			word_txt[j][k] = str[i];
			k++;
		}

		i++;
	}
}


int str_exist(char str[MxWordL], char group[MxWord][MxWordL]){

	int i;

	for(i = 0; group[i][0] != '\0';i++){
	
		if( comparar_str( str,group[i] )){ return 1; }
	
	}
	return 0;

}


void subs_str(char str_og[MxWordL],char str_new[MxWordL]){

	int i;
	//vai substituir os characters pelos da str nova
	for(i = 0;( str_new[i] != '\0' ); i++){	
		str_og[i] = str_new[i];
	}

	str_og[i] = '\0';

}

void trocar(char og[MxWord][MxWordL],char new[MxWord][MxWordL],char text[MxTxtL]){

	char word_text[MxWord][MxWordL] = {};
	int i,j,n;

	//primeiro ver se as palavras novas existem todas no texto 

	dividir_texto(text,word_text);


	for(i = 0;( new[i][0] != '\0' );i++ ){

		if( !( str_exist( og[i],word_text) ) ){ 
			printf("\n\nErro na introducao de dados\nNao existem todas as palavras na string original\n");
		}

	}

	//encontrar as palavras no texto 
	printa(new);
	printa(og);
	for(i = 0; og[i][0] != '\0'; i++){

		for(j = 0 ; word_text[j][0] != '\0'; j++){	

			if( comparar_str( og[i],word_text[j] ) ){ subs_str( word_text[j],new[i] ); } 
			
			// se as strings forem iguais vou substituilas
		}

	}
	//transformar word_text em text

	n = 0; //vai representar a soma de i + j para localizar a str texto
	for(i = 0; word_text[i][0] != '\0' ;i++){

		for(j = 0; word_text[i][j]!= '\0' ; j++){
			text[n] = word_text[i][j];
			n++;
		}
		text[n] = ' ';
		n++;

	}
	n--;
	text[n] = '\0';
}

int main(){ 

	char text[MxTxtL] = {"Esta e uma longa string de caracteres"}, og_word[MxWord][MxWordL] = {},new_word[MxWord][MxWordL] = {};
	int nwords,nr_wrd_og = 7;

	system("clear");
	printf("Texto inicial\n%s\n\n",text);
	printf("Quantas palavras tem a lista de substituicao?\n");

	if((scanf(" %d",&nwords) < 0) || (nwords > nr_wrd_og)){ exit(1); }
	
	getchar();

	printf("Palavras a desaparecer: ");
	ler_palavras(og_word,nwords);

	printf("Palavras a colocar ");
	ler_palavras(new_word,nwords);

	trocar(og_word,new_word,text);

	printf("\n%s",text);

	return 0;
}
