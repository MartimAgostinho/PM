#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXWORDLENGHT 100
#define MAXNAMES 815
#define MAXSURNAMES 752
#define MAXFILELIST 186
#define HISTL 15
#define HISTCOL 90

//escreve a matriz com o aviao
void print_plane(char matriz[7][MAXFILELIST*2]){

    int i,j;
    for(i = 0; i < 7;i++){

        for(j = 0; matriz[i][j] != '\0';j++){ printf("%c",matriz[i][j]); }
        printf("\n");
    }
}

//escreve a matriz do histograma
void print_histogram(char matriz[HISTL][HISTCOL]){

    int i,j;
    for(i = 0; i < HISTL;i++){

        for(j = 0; j < HISTCOL;j++){ printf("%c",matriz[i][j]); }
        printf("\n");
    }
}

typedef struct seatinfo{

    char occupied;              
    char name [MAXWORDLENGHT];  
    char checked_in;            
    int  id_luggage;            
    int  id_reservation_code;  

}seatinfo;

//--------------------------------

//recebe duas strings compara e devolve 1 ou 0 
//str1 < str2 idealmente
int rand_int(int min,int max){ return (rand() % (max + 1)) + min; } 

int compare_str(char *str1,char *str2){
    
    int i;

    for (i = 0; str1[i] != '\0' ; i++){

        if( str1[i] != str2[i] ){ return 0; }
    }

    if(str1[i] != str2[i]){ return 0; } 
        
    return 1;
}

//funcao recebe 2 strings e iguala str1 a str2
void insert_str(char *str1,char *str2){

    int i;

    for(i = 0;str2[i] != '\0';i++){ str1[i] = str2[i]; }
    str1[i] = '\0';
}

// adiciona a str1 e str2 a fstr, assume que fstr tem espaco para str1 + str2
void add_str(char *fstr,char *str1,char *str2){

    int i,n;

    for(i = 0;str1[i] != '\0';i++){ fstr[i] = str1[i]; }
    for(n = 0;str2[n] != '\0';n++){ fstr[i + n] = str2[n]; }
    fstr[n + i] = '\0'; 

}

//evitar inputs nao desejados 
char clear_inp(){

    int x;
    while ((x = getchar()) != '\n' && x != EOF) { }
    return 1;
}

//espera por um enter e limpa o ecra 'a' para limpar input
void wait_enter(int a){

    printf("\nPlease press Enter to continue.\n");
    if(a){ clear_inp(); }
    while(getchar() != '\n'){}
    system("clear");
}

//tenta ler o ficheiro e devolve 1 ou 0 a var plane_model fica com o nome do ficheiro 
int read_plane(/*FILE **fp*/char *plane_model){
    
    FILE *fp;

    insert_str(plane_model, "Airbus");
    printf("Please indicate the aircraft type (Ex. A318): ");
    scanf(" A%s",&plane_model[6]);               

    if( ( fp = fopen(plane_model, "r") ) == NULL ){

        printf("Error opening file %s. Please correct it\n",plane_model);
        wait_enter(1);
        return 0;
    }

    fclose(fp);
    return 1;
}

//recebe um apontador para o ficheiro e duas variaveis que representao os lugares executivos/turista
// "devolve" o numero de lugares executivos e turistas fecha o ficheiro
int read_plane_struct(char *plane_name,int *ex_rows,int *tours_rows){

    char finp[MAXWORDLENGHT];
    FILE *fp;
    
    if ( (fp = fopen(plane_name, "r")) == NULL ){

        printf("Error opening file %s.\n",plane_name);
        return 0;
    } 
    
    while( (fscanf(fp, " %s",finp ) ) != EOF ){ 

        if( compare_str("abcd",finp) ){ 
            
            (*ex_rows)++; 
            continue;
        }
        (*tours_rows)++;
    }
    fclose(fp);
    return 1;
}

//recebe um apontador para numero do model, para o nome do modelo o nome do voou
//carrega as informacoes de um voou se for bem sucedido devolve 1 se nao devolve 0
int load_flight(seatinfo flight[MAXFILELIST],int *model,char plane_model[10] ,char *flight_name){

    FILE *fflight;

    insert_str(plane_model, "Airbus3");

    if ( ( fflight = fopen(flight_name,"rb") ) == NULL ) { 
        
        printf("Error opening file %s.\n",flight_name);
        return 0;
    }
    
    fread(model,sizeof(int),1,fflight);
    fread(flight, sizeof(seatinfo), MAXFILELIST, fflight);

    plane_model[7] = '0' + ( (*model - 300)/10 );
    plane_model[8] = '0' + (*model - (*model/10) *10);
    plane_model[9] = '\0';
    fclose(fflight);
    return 1;
}

//Esta funcao tenta ler quanto lugares toristicos ou executivos tem o aviao de um ficheiro de voou
//recebe apontares para as variaveis onde sera guardada a informacao, e strings com o nome do voou e modelo do aviao
//devolve 1 ou 0 dependendo do sucesso
int read_flight_rows(char *flight_name,int *ex_rows,int *tour_rows,char plane_model[10]){

    int n_model;
    seatinfo flight_seat[MAXFILELIST];

    insert_str(plane_model, "Airbus");
    
    if (!load_flight(flight_seat, &n_model, plane_model, flight_name) ){ return 0; }
    
    read_plane_struct(plane_model,ex_rows,tour_rows);
    return 1;
}

//Tenta carregar os lugares de um ficheiro de voou para uma matriz
//recebe o nome do voou, e a matriz onde sera escrita a estrutura
int load_flight_struct(char *flight_name,char plane_struct[7][MAXFILELIST*2]){
    
    char finp[MAXWORDLENGHT];
    char plane_model[10] ;
    int  n_model;
    int  i ,j, n, seat_position;
    int  ex_rows = 0, tour_rows = 0, n_rows_total = 0; 
    FILE *fplane;
    seatinfo flight_seat[MAXFILELIST];
 
    if (!read_flight_rows(flight_name, &ex_rows, &tour_rows,plane_model) ) { return 0; }

    n_rows_total = ex_rows + tour_rows;

    fplane = fopen(plane_model,"r");

    if ( !load_flight(flight_seat,&n_model,plane_model,flight_name) ) { return 0; }

    seat_position = 1;
    for(j = 0;j < (n_rows_total * 2 ) ;j++){
        
        if( !(j % 2) ){ 

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
                    
                    plane_struct[i][j-1] = ' '; 
                }
                
                else{ plane_struct[i][j-1] = '0' + (seat_position/10); }

                plane_struct[i][++j-1] = '0' + (seat_position - (seat_position/10)*10);
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
    
    for(i = 0; i < MAXFILELIST;i++){

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
                j = 3 + (( i/6 ) * 2);
                if(n > 2) { n++;}
                plane_struct[n][j] = '.';
            }
        }
    }
    plane_struct[3][0] = ' ';
    fclose(fplane);
    return 1;
}

//atualiza uma lugar num voou existente 
//recebe a informacao nova do lugar a posicao na lista e nome do voou
int write_seat(seatinfo seat, int n_list,char *flight_code){

    int model;
    FILE *fflight;
    seatinfo flight_seat[MAXFILELIST];

    if( (fflight = fopen(flight_code, "rb") ) == NULL) {

        printf("Error opening file %s",flight_code);
        return 0;
    }

    fread(&model,sizeof(int),1,fflight);
    fread(&flight_seat, sizeof(seatinfo), MAXFILELIST, fflight);

    fclose(fflight);
    fflight = fopen(flight_code, "wb");
    
    flight_seat[n_list].occupied            = seat.occupied;
    flight_seat[n_list].checked_in          = seat.checked_in;
    flight_seat[n_list].id_luggage          = seat.id_luggage;
    flight_seat[n_list].id_reservation_code = seat.id_reservation_code;
    insert_str(flight_seat[n_list].name, seat.name);

    fwrite(&model, sizeof(int), 1, fflight);
    fwrite(flight_seat, sizeof(seatinfo), MAXFILELIST , fflight);

    fclose(fflight);

    return 1;
}

//cria o ficheiro de voou
void write_plane(char *flight_name,char *plane_model,char *flight){

    FILE *fflight;                                
    int  ex_rows = 0,tours_rows = 0;
    int  n_seats,plane_nr = 300;
    int  i;
    seatinfo flight_seat[MAXFILELIST]; 

    if( !read_plane_struct(plane_model, &ex_rows,&tours_rows) ){ return; }
    n_seats = (ex_rows * 4) + ( tours_rows * 6 );

    for(i = 0;i < n_seats;i++){ flight_seat[i].occupied = 0; }

    plane_nr += (plane_model[7] - '0') * 10 + (plane_model[8] - '0');
   
    insert_str(flight, flight_name);

    fflight = fopen(flight_name, "wb");

    fwrite(&plane_nr, sizeof(int), 1, fflight);
    fwrite(flight_seat, sizeof(seatinfo), MAXFILELIST, fflight);
    
    fclose(fflight);
    return ;
}

//cria o ficheiro de voou
//recebe um apontador para guardar o nome do voou
int assign_plane(char *flight){

    char flight_name[MAXWORDLENGHT] ;
    char plane_model[10];

    printf("Write a flight code without blank spaces (Ex. TP1048): ");
    scanf(" %s",flight_name);

    if ( !(read_plane( plane_model)) ) { return 0; }

    write_plane(flight_name, plane_model, flight);

    return 1;
}

void show_struct(){ //pergunta qual o modelo do aviao e escreve o numero de lugares executivos/turista

    char plane_model[MAXWORDLENGHT]; 
    int ex_rows = 0,tours_rows = 0;             

    if ( !(read_plane(plane_model) ) ) { return; }

    read_plane_struct(plane_model, &ex_rows, &tours_rows);
    
    printf("\n%s:\nExecutiv rows = %d\nTouristic rows = %d\n",plane_model,ex_rows,tours_rows);
    
    wait_enter(1);
}

//mostra a ocupacao do aviao
void show_flight_seats(){

    char plane_struct[7][MAXFILELIST*2] = {};      
    char flight_name[MAXWORDLENGHT];
    char plane_model[10];
    int  n_model;
    seatinfo flight_seat[MAXFILELIST] = {};
    
    printf("Which is the flight that you want to see the occupancy? ");
    scanf(" %s",flight_name);
    
    if (!load_flight(flight_seat, &n_model, plane_model, flight_name) ){ return; }

    if( !load_flight_struct(flight_name, plane_struct) ) { 
    
        return;
    } 
    
    print_plane(plane_struct);

    wait_enter(1);
}

//Mostra os passageiros de um voou
void show_passangers_names(){

    int i;
    int n_model,row,ex_rows,tour_rows;
    char seat;
    char flight_name[MAXWORDLENGHT];
    char plane_model[10];
    seatinfo flight[MAXFILELIST];

    printf("Which is the flight that you want to see the reservations? ");
    scanf(" %s",flight_name);

    if( !load_flight(flight, &n_model, plane_model, flight_name) ) { return; }
    
    read_plane_struct(plane_model, &ex_rows, &tour_rows);

    printf("\n\nPassengers\n");
    printf("    Executive:\n");

    for(i = 0;i < (ex_rows * 4);i++ ){ 
        
        if( flight[i].occupied ){
            
            row  = ( i/4) + 1;
            seat = 'a' + i % 4 ;
            printf("        Row %d, seat %c: name = %s\n",row,seat,flight[i].name);
        }
    }

    printf("    Touristic:\n");
    
    for(;i < (tour_rows * 6);i++ ){ 
        
        if( flight[i].occupied ){
           
            row  = ex_rows + 1 + ((i - (ex_rows * 4))/6);
            seat = 'a' + i % 6 ;
            printf("        Row %d, seat %c: name = %s\n",row,seat,flight[i].name);
        }
    }
    wait_enter(1);
}

//reserva um voou
void reserve_flight(){
    
    char seat,tinp;
    char plane_struct[7][MAXFILELIST*2];
    char flight_code[MAXWORDLENGHT],name[MAXWORDLENGHT];
    char plane_model[10];
    int  luggage,reservation;
    int  row,n_model,lp,p,exit = 0;
    int  ex_rows,tour_rows;
    seatinfo flight_seat[MAXFILELIST];
    
    system("clear");

    printf("What is the flight code for the reservation? ");
    scanf(" %s",flight_code);
        
    if(!load_flight(flight_seat, &n_model, plane_model, flight_code) ){ 
        
        wait_enter(1);
        return;
    }
        
    if(!load_flight_struct(flight_code, plane_struct)) { 

        printf("Error loading flight struct\n");
        wait_enter(0);
        return;
    }
    read_plane_struct(plane_model, &ex_rows, &tour_rows);
    
    do{
        system("clear");

        printf("        The reserved seats have the mark .\n\n");
        print_plane(plane_struct);

        switch (p) {
        
            case 0:
                printf("    Insert the row number for the reservation? ");
                
                if( ((scanf(" %d%c",&row,&tinp) != 2 ) || tinp != '\n') || (( row < 0 ) || ( row > ( ex_rows + tour_rows ))) ){ 

                    printf("Wrong row.");
                    wait_enter(1);
                    continue;
                }
                p =  1;

            case 1:
                printf("    What is the seat in this row? ");

                if( (scanf(" %c%c",&seat,&tinp) !=2) || tinp != '\n' || ((( seat - 'a' ) < 0) || (( seat - 'a' ) > 6)) || ( (( seat - 'a' ) > 3) && row < ex_rows ) ){ 
                                    
                    printf("Wrong seat letter\n");
                    wait_enter(1);
                    continue;
                }

                if( row > ex_rows ){

                    lp = ((row - ex_rows - 1) * 6) + ( ex_rows * 4 ) + seat - 'a';
                }

                else { lp = ((row - 1 ) * 4) + seat - 'a'; }

                if( flight_seat[lp].occupied ){ 

                    printf("This seat is already reserved.\n");
                    p = 0;
                    wait_enter(0);
                    continue;
                }
                p = 2;

            case 2:
                
                printf("Please write the name and surname: ");
                scanf("%[^\n]",name);
                p = 3;

            case 3:
                
                printf("Please write a number for the identifier of the luggage: ");
                if(  scanf("%d%c",&luggage,&tinp) != 2 || tinp != '\n') { 
                    
                    printf("Please enter a number.\n");
                    wait_enter(1);
                    continue;
                }
                p = 4;

            case 4:

                printf("Please write a number for the reservation code: ");
                if(  scanf(" %d%c",&reservation,&tinp) != 2 || tinp != '\n') { 
                    
                    printf("Please enter a number.\n");
                    wait_enter(1);
                    continue;
                }
                exit = 1;
                break;
        }
    }while( !exit );
    
    flight_seat[lp].occupied = 1;
    flight_seat[lp].checked_in = 1;
    flight_seat[lp].id_luggage = luggage;
    flight_seat[lp].id_reservation_code = reservation;
    insert_str(flight_seat[lp].name, name);
    
    write_seat(flight_seat[lp], lp, flight_code);
        
    wait_enter(0);
}

//mudar a reserva de um lugar num voou
void change_reservation(){

    char flight_code[MAXWORDLENGHT],plane_struct[7][MAXFILELIST*2];
    char plane_model[10] ;
    char tinp,seat,name[MAXWORDLENGHT];
    int row,ex_rows,tour_rows;
    int  lp,lp1,n_model,exit = 0,p = 0;
    seatinfo flight_seat[MAXFILELIST],new_seat,empty;
    
    empty.occupied      = 0;
    new_seat.occupied   = 1;

    printf("What is the flight code where you have the reservation? ");
    scanf(" %s",flight_code);

    if(!load_flight(flight_seat, &n_model, plane_model, flight_code) ){ 
        
        wait_enter(1);
        return;
    }
        
    if(!load_flight_struct(flight_code, plane_struct)) { 

        printf("Error loading flight struct %s\n",flight_code);
        wait_enter(1);
        return;
    }
    read_plane_struct(plane_model, &ex_rows, &tour_rows);

    do{
        system("clear");

        printf("        The reserved seats have the mark .\n\n");
        print_plane(plane_struct);

        switch (p) {
        
            case 0:
                printf("    What is your original row? ");
                
                if( ((scanf(" %d%c",&row,&tinp) != 2 ) || tinp != '\n') || (( row < 0 ) || ( row > ( ex_rows + tour_rows ))) ){ 

                    printf("Wrong row.");
                    wait_enter(1);
                    continue;
                }
                p =  1;

            case 1:
                printf("    What is your original seat in this row (a, b, ...)?");

                if( (scanf(" %c%c",&seat,&tinp) != 2) || tinp != '\n' || ((( seat - 'a' ) < 0) || (( seat - 'a' ) > 6)) || ( (( seat - 'a' ) > 3) && row < ex_rows ) ){ 
                                    
                    printf("Wrong seat letter\n");
                    wait_enter(1);
                    continue;
                }

                if( row > ex_rows ){

                    lp = ((row - ex_rows - 1) * 6) + ( ex_rows * 4 ) + seat - 'a';
                }

                else { lp = ((row - 1 ) * 4) + seat - 'a'; }

                if( !flight_seat[lp].occupied ){ 

                    printf("This seat is empty.\n");
                    wait_enter(0);
                    continue;
                }
                lp1 = lp;
                p = 2;

            case 2:
                
                printf("Just for testing:-------> the reservation name is: %s\n",flight_seat[lp].name);
                printf("Write your name and surname: ");
                scanf("%[^\n]",name);
                if( !compare_str(flight_seat[lp].name, name)){

                    printf("Wrong name. You must start the process again.\n");
                    p = 0;
                    wait_enter(1);
                    continue;
                }
                insert_str(new_seat.name, name);
                p = 3;

            case 3:

                printf("\n\n    What is the row for the new reservation? ");
                 
                if( ((scanf(" %d%c",&row,&tinp) != 2 ) || tinp != '\n') || (( row < 0 ) || ( row > ( ex_rows + tour_rows ))) ){ 

                    printf("Wrong row.");
                    wait_enter(1);
                    continue;
                }
                p = 4;

            case 4:
                printf("    What is the seat in this row? ");
                
                if( (scanf(" %c%c",&seat,&tinp) !=2) || tinp != '\n' || ((( seat - 'a' ) < 0) || (( seat - 'a' ) > 6)) || ( (( seat - 'a' ) > 3) && row < ex_rows ) ){ 
                                    
                    printf("Wrong seat letter\n");
                    wait_enter(1);
                    continue;
                }

                if( row > ex_rows ){ 
                   
                    lp = ((row - ex_rows - 1) * 6) + ( ex_rows * 4 ) + seat - 'a'; 
                }

                else { lp = ((row - 1 ) * 4) + seat - 'a'; }

                if( flight_seat[lp].occupied ){ 

                    printf("This seat is occupied.\n");
                    p = 3;
                    wait_enter(0);
                    continue;
                }
                exit = 1;
                break;
        }

    }while( !exit );

    write_seat(flight_seat[lp1], lp, flight_code);   
    write_seat(empty, lp1, flight_code);
    wait_enter(0);
}

//cria e enche um voou com passageiros aleatorios
void fill_random(){

    char flight_name[MAXWORDLENGHT], plane_model[10] ;
    char names[MAXNAMES][MAXWORDLENGHT], surnames[MAXSURNAMES][MAXWORDLENGHT];
    char full_name[MAXWORDLENGHT];
    int i,nr_model,ex_rows,tour_rows,nr_seat,seat,nt_seats;
    FILE *fnames, *fsurnames, *fflight;
    seatinfo flight_seat[MAXFILELIST];

    fnames      = fopen("names","r");
    fsurnames   = fopen("surnames","r");
    
    if( ( fnames == NULL ) || ( fsurnames == NULL ) ){ 

        printf("Error opening names and or surnames file\n");
        return; 
    }
    
    i = 0;

    while( (fscanf(fnames, " %s",names[i] ) ) != EOF ){ i++; }
    
    i = 0;
    
    while( (fscanf(fsurnames, " %s",surnames[i] ) ) != EOF ){ i++; }
    
    //criar voou
    if( !assign_plane(flight_name) ){ return; } 

    if(!load_flight(flight_seat, &nr_model, plane_model, flight_name)){ 
        
        wait_enter(0);
        return;
    }

    read_plane_struct(plane_model, &ex_rows, &tour_rows);
    
    nt_seats = (ex_rows * 4) + (tour_rows * 6);
    nr_seat  = rand_int(1, ( nt_seats ));

    printf("The aircraft has %d seats and %d seats will be reserved (%0.2f%%)\n",nt_seats,nr_seat,((float) (nr_seat * 100)/nt_seats ));

    for(i = 0;i < nr_seat; i++ ){

        seat = rand_int(5, nt_seats);

        if( flight_seat[seat].occupied ){ 
            
            --i;
            continue;
        }
        
        flight_seat[seat].occupied              = 1;
        flight_seat[seat].checked_in            = 1;
        flight_seat[seat].id_luggage            = rand_int(0, 500);
        flight_seat[seat].id_reservation_code   = rand_int(0, 500);
        
        add_str(full_name, names[rand_int(0, MAXNAMES)], " ");
        add_str(full_name, full_name, surnames[ rand_int(0, rand_int(0, MAXSURNAMES)) ]);
        insert_str(flight_seat[seat].name,full_name);
        insert_str(full_name, " ");
    }
    
    fflight = fopen(flight_name, "wb");
    fwrite(&nr_model, sizeof(int), 1, fflight);
    fwrite(flight_seat, sizeof(seatinfo), nt_seats, fflight);
    
    fclose(fflight);
    fclose(fnames);
    fclose(fsurnames);
    wait_enter(1);
}

//mostra o histograma de um voou
void show_flight_histogram(){

    char histogram[HISTL][HISTCOL] = {};
    char flight_name[MAXWORDLENGHT],plane_model[10];
    int nr_model,nt_seats;
    int n_seats_occupied = 0, n_ex_seats = 0, n_tour_seats = 0;
    int n_window_ex = 0,n_window_tour = 0;
    int n_hall = 0,n_middle = 0;
    int i,j,n_star;
    int ex_rows,tour_rows;
    seatinfo fligh_seat[MAXFILELIST];

    printf("Which is the flight that you want to see the histogram? ");
    scanf(" %s",flight_name);

    if( !load_flight(fligh_seat, &nr_model, plane_model, flight_name) ){ return; } 

    if( !read_flight_rows(flight_name, &ex_rows, &tour_rows, plane_model) ){ return; }

    nt_seats = (ex_rows * 4) + (tour_rows * 6);

    for(i = 0;i < nt_seats;i++){ 

        if( fligh_seat[i].occupied && i < (ex_rows * 4)){ n_ex_seats++; }

        else if( fligh_seat[i].occupied ){ n_tour_seats++; }
    }
    n_seats_occupied = n_ex_seats + n_tour_seats;

    for(i = 0;i < nt_seats;i++ ){

        if( !fligh_seat[i].occupied ){ continue; }

        if( i < (ex_rows * 4) ){ 

            if( !(i % 4) || ('a' + (i % 4) ) == 'd' ){ n_window_ex++; }
        }
        else{
            
            if( !((i - (ex_rows * 4)) % 6) || ('a' + ((i - (ex_rows * 4)) % 6) ) == 'f' ){ n_window_tour++; }
        }
    }

    for(i = 0;i < nt_seats;i++ ){

        if( !fligh_seat[i].occupied ){ continue; }

        if( i < (ex_rows * 4) ){ continue; }
        
        else{
            
            if( (('a' + ((i - (ex_rows * 4)) % 6) ) == 'b') || (('a' + ((i - (ex_rows * 4)) % 6) ) == 'e') ){ n_middle++; }
        }
    }

    for(i = 0;i < nt_seats;i++ ){

        if( !fligh_seat[i].occupied ){ continue; }

        if( i < (ex_rows * 4) ){ 

            if( ('a' + (i % 4) ) == 'b' || ('a' + (i % 4) ) == 'c' ){ n_hall++; }
        }
        else{
            
            if( ('a' + ((i - (ex_rows * 4)) % 6) ) == 'c' || ('a' + ((i - (ex_rows * 4)) % 6) ) == 'd' ){ 
                
                n_hall++;
            }
        }
    }

    for( i = 0;i < HISTL;i++ ){ 
        if( !(i % 2) ){

            for(j = 0;j < HISTCOL;j++ ){ histogram[i][j] = '-'; }
        }
     }

    insert_str(histogram[1], "Occuppied seats ");
    insert_str(histogram[3], "Executive seats ");
    insert_str(histogram[5], "Touristic seats ");
    insert_str(histogram[7], "Window Executive");
    insert_str(histogram[9], "Window Tourist  ");
    insert_str(histogram[11], "Corridor seat   ");
    insert_str(histogram[13], "Middle seat     ");

    for(i = 1;i < (HISTL - 1);i++){ histogram[i][16] = '|'; }
    
    histogram[0][16] = '+';
    histogram[HISTL - 1][16] = '+';

    printf("\nOccuppied seats:                    %0.2f%%\n", (float)(n_seats_occupied * 100 ) / nt_seats );
    printf("Occupied executive seats :          %0.2f%%\n",(float)( n_ex_seats * 100 ) / (ex_rows * 4));
    printf("Occupied tourist seats :            %0.2f%%\n",(float)( n_tour_seats * 100 ) / (tour_rows * 6));
    printf("Occupied executive window seats :   %0.2f%%\n",(float)(n_window_ex * 100 ) / (ex_rows * 4));
    printf("Occupied tourist window seats :     %0.2f%%\n",(float)(n_window_tour * 100 ) / (tour_rows * 6));
    printf("Occupied corridor seats :           %0.2f%%\n",(float)(n_hall * 100 ) / ((ex_rows + tour_rows) * 2));
    printf("Occupied \"middle\" seats :           %0.2f%%\n",(float)(n_middle * 100 ) / (tour_rows * 2));

    n_star = (n_seats_occupied * 70 ) / nt_seats;
    for(i = 0;i < n_star ;i++){ histogram[1][17+i] = '*'; }

    n_star = (n_ex_seats * 70 ) / (ex_rows * 4);
    for(i = 0;i < n_star ;i++){ histogram[3][17+i] = '*'; }

    n_star = (n_tour_seats * 70 ) / (tour_rows * 6);
    for(i = 0;i < n_star ;i++){ histogram[5][17+i] = '*'; }

    n_star = (n_window_ex * 70 ) / (ex_rows * 4);
    for(i = 0;i < n_star ;i++){ histogram[7][17+i] = '*'; }

    n_star = (n_window_tour * 70 ) / (tour_rows * 6);
    for(i = 0;i < n_star ;i++){ histogram[9][17+i] = '*'; }

    n_star = (n_hall * 70 ) / nt_seats;
    for(i = 0;i < n_star ;i++){ histogram[11][17+i] = '*'; }

    n_star = (n_middle * 70 ) / nt_seats;
    for(i = 0;i < n_star ;i++){ histogram[13][17+i] = '*'; }
    
    print_histogram(histogram);
    wait_enter(1);
}

void menu(){ 

    char inpt[MAXWORDLENGHT];
    char empty[MAXWORDLENGHT];
    int exit = 0;

    srand(time(NULL));
    system("clear");
    
    while(!exit){
        
        printf("\n\n           aircraft business\n");
        printf("0 - exit\n");
        printf("1 - show the structure of a plane\n");
        printf("2 - show the occupancy of a flight\n");
        printf("3 - show the passenger names with a reservation for this flight\n\n");
        printf("4 - reserve a flight with seat number\n");
        printf("5 - change the seat of a reservation\n");
        printf("6 - assign a plane to a specific flight (opening of a flight)\n\n");
        printf("7 - Fill in a flight with random passengers\n\n");
        printf("8 - Histogram of flight occupancy per type of seat\n");
        printf("9 - Generation of the files \"names\" and \"surnames\"\n");
        
        scanf(" %s",inpt);

        switch (inpt[0]) { 
       
            case '0': exit = 1;
                break;

            case '1': show_struct();
                break;
            
            case '2':show_flight_seats();
                break;
            
            case '3':show_passangers_names();
                break;
            
            case '4':reserve_flight();
                break;
            
            case '5':change_reservation();
                break;
            
            case '6':assign_plane(empty);
                wait_enter(1);
                break;
            
            case '7':fill_random();
                break;
            
            case '8':show_flight_histogram();
                break;
            
            case '9':
                break;

            default:printf("\nErro na introducao de dados!\n\n");
                continue;
        }
    }
}

int main(int narg,char *argv[]){

    char empty[MAXWORDLENGHT],plane_model[10] = "Airbus3";
    int ex_rows = 0,tour_rows = 0;

    if(narg - 1){
        
        if(compare_str("-h", argv[1])){
            
            printf("\n   Sintax:  ./demo  flight_name    aircraft_type  \n");
            printf("         or:  ./demo  aircraftType   \n\n");
            printf("    Example:  ./demo  TP1048      A318\n");
            printf("         or:  ./demo  A318\n");
            return 0;
        }
        else if( narg > 2 ){

            plane_model[7] = argv[2][2];
            plane_model[8] = argv[2][3];
            plane_model[9] = '\0';
            write_plane(argv[1], plane_model, empty); 
        }
        else {

            plane_model[7] = argv[1][2];
            plane_model[8] = argv[1][3];
            plane_model[9] = '\0';

            if( !read_plane_struct(plane_model, &ex_rows, &tour_rows) ){ 
                
                return 1;
            }

            printf("\n%s:\nExecutiv rows = %d\nTouristic rows = %d\n",plane_model,ex_rows,tour_rows);
        }  
    }
    else { menu(); }

    return 0;
}
