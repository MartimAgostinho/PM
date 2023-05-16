#include <stdio.h>
#include <stdlib.h>
#define MAXWORDLENGHT 100

typedef struct dados_lugar{

    char occupied;              // 0 ou 1
    char name [100];            
    char checked_in;            
    int  id_luggage;
    int  id_reservation_code;

}seatinfo;

void print_matriz(char matriz[7][1000], int c){

    int i,j;
    for(i = 0; i < 7;i++){

        for(j = 0; j <= c;j++){ printf("%c",matriz[i][j]); }
        printf("\n");
    }

}

int comparar_str(char *str1,char *str2){
    int i;

    for (i = 0; str1[i] != '\0' ; i++){

        if( str1[i] != str2[i] ){ return 0; }
    }

    if(str1[i] != str2[i]){ return 0; } //evitar strings com o inicio igual
        
    return 1;
}

void read_plane_struct(FILE **fp,int *ex_rows,int *tours_rows){

    char finp[MAXWORDLENGHT];

    while( (fscanf(*fp, " %s",finp ) ) != EOF ){ // enquanto houverem linhas para ler

        if( comparar_str("abcd",finp) ){ //so os banco executivos tem str = abcd
            (*ex_rows)++; 
            continue;
        }
        (*tours_rows)++;//quase um else if por causa do continue
    }
    fclose(*fp);

}

void show_flight_seatsv2(){

    char plane_struct[7][1000] = {};
    char finp[MAXWORDLENGHT];
    char flight_name[MAXWORDLENGHT];
    char plane_model[MAXWORDLENGHT] = "Airbus3";
    int  n_model;
    int  i ,j, n, seat_position;
    int  ex_rows , tour_rows, n_rows_total,n_seats; 
    FILE *fflight,*fplane;
    seatinfo flight_seat[186];
 
    printf("Write a flight code without blank spaces (Ex. TP1048): ");
    scanf(" %s",flight_name);


    if ( ( fflight = fopen(flight_name,"rb") ) == NULL ) { 
        printf("Error opening file %s.\n",flight_name);
        return;
    }
    
    fread(&n_model,sizeof(int),1,fflight);
    fread(flight_seat, sizeof(seatinfo), 186, fflight);

    plane_model[7] = '0' + ( (n_model - 300)/10 );
    plane_model[8] = '0' + (n_model - (n_model/10) *10);
    
    fplane = fopen(plane_model,"r");
    
    read_plane_struct(&fplane,&ex_rows,&tour_rows);

    n_rows_total = ex_rows + tour_rows;

    fplane = fopen(plane_model,"r");

    //escrever coluna a coluna 
    seat_position = 1;
    for(j = 0;j < (n_rows_total * 2 ) ;j++){
        
        if( !(j % 2) || (j == 0) ){ 

            for(i = 0;i < 7;i++) { 
                if( i != 3 ) { plane_struct[i][j] = ' '; }
            }
            continue;
        }

        fscanf(fplane, " %s",finp );
        i = 0;
        n = 0;
        if(j < (1 + ex_rows * 2) ){  

            plane_struct[i][j] = ' ';
            plane_struct[6][j] = ' ';
            i++;
        }
        
        while(finp[n] != '\0'){
            
            if( i == 3){ 

                if (!(seat_position/10)) { 
                    plane_struct[i][j] = ' '; 
                }
                
                else{ 
                    plane_struct[i][j] = '0' + (seat_position/10); 
                }

                plane_struct[i][++j] = '0' + (seat_position - (seat_position/10)*10);
                seat_position++;
                i++;
                j--;
                continue;
            }
            else { 
                plane_struct[i][j] = finp[n]; 
                n++;
            }
            i++;
        }
    }
    
    for(i = 0; i < 186;i++){

        if(flight_seat[i].occupied){
            
            if( i < (ex_rows * 4) ){
                
                j = 1 + ( i/4) * 2;
                n =  i % 4 ;
                if( n > 1 ){ n++; }
                n++;
                plane_struct[n][j] = '.';

            }
            else {

                n = i % 6;
                j = 1 + ( i/6 ) * 2;
                if(n > 2) { n++;}
                plane_struct[n][j] = '.';
            }
        }
    }
    
    print_matriz(plane_struct,n_rows_total * 2);

    fclose(fplane);
    fclose(fflight);
}

//FIXME NAO FUNFA
void show_flight_seats(){

    int i,j,n_seat,n_char = 0,k;
    int ex_rows = 3, tour_rows = 17; //FIXME valores de variaveis provisorios
    int n_rows_total,fmodel,n_total_seats;  
    char flight_name[MAXWORDLENGHT] ,plane_model[MAXWORDLENGHT] = "Airbus3";       
    char plane_struct[7][1000] = {};//TODO defenir n maximo de colunas
    seatinfo flight_seat[186];
    FILE *fflight,*fplane;

    //TODO ler ex_rows e tour_rows
    
    //pedir nome do ficheiro
   
    n_total_seats = (ex_rows * 4)+ ( tour_rows * 6 );
    n_rows_total  = ex_rows + tour_rows;
    
    //TODO ESCREvER LITERALMENTE FICHEIRO NA MATRIZ
    //criar a matriz da estrutura do aviao
    for(j = 0;j < 7;j++){ //j = linhas e i = colunas
        
        if(j == 3){//linha dos numeros

            n_seat = 1;   //numero do lugar
            
            for(i = 0;i < (n_rows_total * 2);i++){
                
                if (!(n_seat/10)) { 
                    plane_struct[j][i] = ' '; 
                }
                
                else{ 
                    plane_struct[j][i] = '0' + (n_seat/10); 
                }

                plane_struct[j][++i] = '0' + (n_seat - (n_seat/10)*10);
                n_seat++;
            }
            continue;
        }

        for(i = 0;i < (n_rows_total*2);i++){ 

            if(i < (ex_rows*2) && (j == 0 || j == 6) ){ plane_struct[j][i] = ' '; } //ex_rows de cima e baixo

            else if( i > (ex_rows*2 - 2) ){ 
                plane_struct[j][i] = ' ';
                plane_struct[j][++i] = 'a' + n_char;

            }
            else {
                plane_struct[j][i] = ' ';
                plane_struct[j][++i] = 'a' + n_char;
            }
        }
        n_char++;
    }
    //print_matriz(plane_struct);

    //TODO delete debug lines
    
    fflight = fopen("TP420", "rb");

    //----------------------

    //TODO ler voou e substituir as letras por pontos
    //TODO alocar memoria para ler o aviao
    //flight_seat = malloc(sizeof(seatinfo) * 186);
    fread(&n_seat, sizeof(int), 1, fflight);
    printf("%d\n",n_seat);
    fread(&flight_seat, sizeof(seatinfo), 186, fflight);
    
    j = 0;
    i = 0; 
    n_seat = 4; //representa o numero de lugares por coluna
    
    while(i < n_total_seats){

        if( i == ( ex_rows * 4 + 1) ){ n_seat = 6; }
            
        if( !(i % 4) && ( i < (ex_rows * 4) ) ) { j = 0; }
        
        else if ( !(i % 6) ) { j = 0; }
        
        if( flight_seat[i].occupied && n_seat == 6) { plane_struct[j][(2 * i/n_seat) + 1] = '.'; }
            
        else if( flight_seat[i].occupied ) { 
            
            plane_struct[j+1][(2 * i/n_seat) + 1] = '.';
        }

        i++;
        j++;
    }

        //alocar memoria para ler os lugares todos 
        //ler os lugares todos e substituir na matriz
    //print_matriz(plane_struct);

    //free(flight_seat);
    fclose(fplane);
    fclose(fflight);
}

int main(){
    
    seatinfo rwar[186];
    FILE *fp;
    int a,i;

    show_flight_seatsv2();
    /*
    fp = fopen("TT22", "rb");

    fread(&a, sizeof(int), 1, fp);
    //while(fread(&(rwar[i]),sizeof(dados_lugar), , FILE *restrict __stream))
    fread(&rwar, sizeof(seatinfo), 108, fp);

    printf("%d\noc %d\nname %s\n%c\n%d\n%d\n",a,rwar[4].occupied,rwar[0].name,rwar[0].checked_in,rwar[0].id_luggage,rwar[0].id_reservation_code);

    for(i = 0; i < 108;i++){

        if(rwar[i].occupied != 0){ printf("%d\nname:%s\n",rwar[i].occupied,rwar[i].name); }
    }
    fclose(fp);
*/
    return 0;
}
