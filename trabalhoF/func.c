#include <stdio.h>

#define MAXWORDLENGHT 1000

typedef struct seatinfo{

    char occupied;              //0 ou 1
    char name [MAXWORDLENGHT];            
    char checked_in;            // 
    int  id_luggage;            //pedir ao user
    int  id_reservation_code;   // ==

}seatinfo;



int write_seat(seatinfo seat, int n_list,char *flight_code){

    

}
