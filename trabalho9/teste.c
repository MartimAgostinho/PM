#include <stdio.h>

int main(){
    
    FILE *fptr;
    char c; 
  
    fptr = fopen("teste.txt", "r");
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }
  
    fclose(fptr);
    return 0;


}
