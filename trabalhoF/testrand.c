#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int rand_int(int min,int max){ 

    int r;

    r = rand();
    max++;
    
    return (r % (max )) + min;
} 

//int rand_int(int min,int max){ return (rand() % (max + 1)) + min; } 

int main(){


    int i,a = 0,b = 0,c = 0,n = 0,d = 0;

    printf("%d\n",rand_int(0, 187));
    for(i = 0; i < 99999;i++){

        n = rand_int(0, 2);
        switch (n) {

            case 0:
                a++;
                break;
            case 1:
                b++;
                break;
            case 2:
                c++;
                break;
            default:
                d++;
        }
    }

    printf("a:%d\nb:%d\nc:%d\nd:%d\n",a,b,c,d);

}
