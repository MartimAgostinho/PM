#include <stdio.h>
#include <stdlib.h>

#define MAXWORDLENGHT 1000

void print_matriz(char matriz[7][MAXWORDLENGHT]){

    int i,j;
    for(i = 0; i < 7;i++){

        for(j = 0; matriz[i][j] != '\0';j++){ printf("%c",matriz[i][j]); }
        printf("\n");
    }

}



void show_flight_seats(){

    int i,j,n_lugar,n_letra = 0,k;
    int ex_rows = 3, tour_rows = 16;
    int n_rows_total = ex_rows + tour_rows;
    char plane_struct[7][1000] = {}; //= {{'a'},{'b'},{'c'},{'d'},{'e'},{'f'},{' '}};
    
    //criar a matriz da estrutura do aviao //TODO ESCREvER LITERALMENTE FICHEIRO NA MATRIZ
    for(j = 0;j < 7;j++){ //j = linhas e i = colunas
        
        if(j == 3){//linha dos numeros

            n_lugar = 1;   //numero do lugar
            
            for(i = 0;i < (n_rows_total * 2);i++){
                
                if (!(n_lugar/10)) { 
                    plane_struct[j][i] = ' '; 
                }
                
                else{ 
                    plane_struct[j][i] = '0' + (n_lugar/10); 
                }

                plane_struct[j][++i] = '0' + (n_lugar - (n_lugar/10)*10);
                n_lugar++;
            }

            continue;
        }
        for(i = 0;i < (n_rows_total*2);i++){ 
    
            if(i < (ex_rows*2) && (j == 0 || j == 6) ){ plane_struct[j][i] = ' '; } //ex_rows de cima e baixo

            else if( i > (ex_rows*2 - 2 ) ){ 
                plane_struct[j][i]   = ' ';
                plane_struct[j][++i] = 'a' + n_letra;

            }
            else {
                plane_struct[j][i]   = ' ';
                plane_struct[j][++i] = 'a' + (n_letra - 1);
            }
        }
        n_letra++;
    }

    print_matriz(plane_struct);

}


struct test{

    int  a;
    int  b;
    char c[5];
};

void printtest(struct test tt){

    printf("%d\n%d\n%s\n",tt.a,tt.b,tt.c);
}



int main(){
 /*
    FILE *fp;
    struct test tt = {
        .a = 0,
        .b = 5,
        .c = "pixa"
    },*rwar;

    rwar = malloc(sizeof(struct test)*7);
    rwar[5].a = 12;
    rwar[5].b = 12;
    printtest(rwar[5]);*/

    show_flight_seats();
    return 0;
}
