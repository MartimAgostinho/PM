/*
* base de dados de cidadaos
* Ficheiro: sirp.c
*/

#include <stdio.h>
#include <stdlib.h>

#define MXCC 500

//Numero de servico social
struct num_serv_sec
{
    int num_serie;
};

void le_nss(struct num_serv_sec *nss ){

    printf("Introduza o numero de servico social: ");
    scanf(" %d", &((*nss).num_serie));
    printf("\n");
}

void print_nss(struct num_serv_sec *nss){

    printf("Numero de seguranca social: %d\n",(*nss).num_serie);
    printf("\n");

}

//Info pessoal
struct info_pessoal
{
    char nome [100];    
    int  dia_nasc;       
    int  mes_nasc;       
    int  ano_nasc;       
    int  altura;         
    char olhos [100];   
    char cabelo [100];  
};

void le_info_pessoal(struct info_pessoal *ifp){

    printf("Introduza o nome: ");
    scanf(" %s",(*ifp).nome);
    
    printf("\nDia de nascimento: ");
    scanf(" %d",&(*ifp).dia_nasc);
    //dia_nasc
    
    printf("\nMes de nascimento: ");
    scanf(" %d",&(*ifp).mes_nasc);
    //mes_nasc
    
    printf("\nAno de nascimento: ");
    scanf(" %d",&(*ifp).ano_nasc);
    //ano_nasc

    printf("\nAltura (em cm): ");
    scanf(" %d",&(*ifp).altura);
    //altura

    printf("\nCor dos olhos: ");
    scanf(" %s",(*ifp).olhos);
    //olhos

    printf("\n Cor do cabelo: ");
    scanf(" %s",(*ifp).cabelo);
   //cabelo
  
    printf("\n");

}

void print_infp(struct info_pessoal *infp){

    printf("Nome: %s\n",(*infp).nome);
    
    printf("Data de nascimento: %d/%d/%d\n", (*infp).dia_nasc, (*infp).mes_nasc, (*infp).ano_nasc);

    printf("Altura (em cm): %d\n",(*infp).altura);

    printf("Cor dos olhos: %s\n",(*infp).olhos);

    printf("Cor do cabelo: %s\n",(*infp).cabelo);    
    printf("\n");

}

//info numeros
struct info_numer
{
    int bi;
    int contribuinte;
    int seg_social;
    int carta_cond;
};

void le_info_numer(struct info_numer *infnr ){

   // int bi;
   printf("Introduza numero do BI: ");
   scanf(" %d",&(*infnr).bi);
   
   // int contribuinte;
   printf("\nIntroduza o numero de contribuinte: ");
   scanf(" %d",&(*infnr).contribuinte);
   
   // int seg_social;
   printf("\nIntroduza o numero de seguranca social: ");
   scanf(" %d",&(*infnr).seg_social);
   
   // int carta_cond;
   printf("\nIntroduza o numero da carta de conducao: ");
   scanf(" %d",&(*infnr).carta_cond);
   
   printf("\n");
}

void print_infnr(struct info_numer *infnr){
 
   printf("Numero do BI: %d\n",(*infnr).bi);
   
   printf("Numero de contribuinte: %d\n",(*infnr).contribuinte);
   
   printf("Numero de seguranca social: %d\n",(*infnr).seg_social);
   
   printf("Numero da carta de conducao: %d\n",(*infnr).carta_cond);
   printf("\n");


}
//Morada
struct morada
{
    char rua [100];
    int  cod_postal1;
    int  cod_postal2;
    char cod_postal3 [100];
};

void le_morada(struct morada *mord){

   // char rua [100];
   printf("\nIntroduza o nome da rua: ");
   scanf(" %s",(*mord).rua);

   // int cod_postal1;
   printf("\nIntroduza o codigo postal 1: ");
   scanf(" %d",&(*mord).cod_postal1);
   
   // int cod_postal2
   printf("\nIntroduza o codigo postal 2: ");
   scanf(" %d",&(*mord).cod_postal2);
   
   // char cod_postal3 [100];
   printf("\nIntroduza o codigo postal 3: ");
   scanf(" %s",(*mord).cod_postal3);
 
   printf("\n");  

}

void print_morada(struct morada *mrd){


   printf("Nome da rua: %s\n",(*mrd).rua);

   printf("Codigo postal 1: %d\n",(*mrd).cod_postal1);
   
   printf("Codigo postal 2: %d\n",(*mrd).cod_postal2);
   
   printf("Codigo postal 3: %s\n",(*mrd).cod_postal3);
   printf("\n");


}
//confidencial
struct confid
{
    char partido [100];
    char clube [100];
};

//TODO Wformat warning!! & no inicio 
void le_confidencial(struct confid *conf){ 

   // char partido [100];
   printf("Introduza o seu partido: ");
   scanf(" %s",(*conf).partido);
   // char clube [100];
   printf("\nIntroduza o clube: ");
   scanf(" %s",(*conf).clube);

   printf("\n");
}

void print_conf(struct confid *conf){

   printf("Partido: %s\n",(*conf).partido);
   printf("Clube: %s\n",(*conf).clube);
   printf("\n");

}

//cidadao
typedef struct cidad
{
    struct num_serv_sec nss;
    struct info_pessoal infp;
    struct info_numer   infn;
    struct morada       address;
    struct confid       clubes;

}cidadao;

void le_cidadao(cidadao *cc){
  
    le_nss(&( (*cc).nss ) );
    le_info_pessoal(&( (*cc).infp ) );
    le_info_numer(&( (*cc).infn ) );
    le_morada(&( (*cc).address ) );
    le_confidencial(&( (*cc).clubes) );

}

void print_cc(cidadao *cc){;

    print_nss(&(*cc).nss);
    print_infp(&(*cc).infp);
    print_infnr(&(*cc).infn);
    print_morada(&(*cc).address);
    print_conf(&(*cc).clubes);
}

void mostrar_nss(cidadao *ccs[MXCC]){

    int i;

    for(i =  0; (i < MXCC) || (ccs[i] == NULL);i++){
    
        printf("O cidadao n%d tem o nss: %d\n",(i+1),(*ccs[i]).nss.num_serie);
    
    }

}

//devolve o proximo lugar vago
int n_vaga(cidadao *cc[MXCC]){

    int i = 0;

    while( cc[i] != NULL ){i++;}

    return i;
}

//------------menu------------ \\

int menu(cidadao *cidd[MXCC]){

    char opc;
    int n;
    int op,vaga;


    system("clear");
    printf("/*********** PROGRAMA SIRP – Registo dos cidadaos **********/\n\n");
    printf("a – Mostrar os número de série de todos os elementos da base de dados\n");
    printf("b – Mostrar toda a informação do cidadão com um certo número (a pedir)\n");
    printf("c – Modificar a informação do cidadão com um certo número (a pedir)\n");
    printf("d – Criar um novo registo para um novo cidadão\n");
    printf("e – Apagar o registo com um certo número (a pedir)\n\n");
    printf("s – Sair do programa\n");
    
    scanf(" %c",&opc);

    switch (opc){

        case 'a' : 
            break;
        
        case 'b' :
            printf("Introduza o nr do cidadao: ");
            scanf(" %d",&n);
            n--;
            print_cc(cidd[n]);
            break;
        
        case 'c' :
            printf("Introduza o nr do cidadao: ");
            scanf(" %d",&n); 
            n--;
            le_cidadao(cidd[n]);
            break;

        case 'd' : 
            le_cidadao( cidd[ n_vaga(cidd) ] );
            break;

        case 'e' :
            
            vaga = n_vaga(cidd);
            
            while(1){
                printf("\nNumero do cc a apagar: ");
                scanf(" %d",&op);
                if( ( op < vaga) && (op > 0) ){ break; }
            }
            
            cidd[op] = NULL;

            break;

        case 's' :  return 0;
            break;

        default: 
            
            printf("Erro na introducao de dados!\n");
            return 1;
    }

    return 1;
}

int main(){

    return 0;
}
