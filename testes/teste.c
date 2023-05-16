#include <stdio.h>
#define MAX3 55

int mm (char hh [], int k, char a, char b) {
    if (hh [k] == a)
        hh [k] = b;
    return ++k;
}
void kk (char tt [], char a, char b) {
 int i = 0;

 while (i < MAX3) {
 i = mm (tt, i, a, b);
 printf("%d\n",i);
 }

}

int main (){

    char a[] ="abaaacaaade;ghijklmnoprstuv";
    int j = 5;
    char b = 'a',c = 'f';

    kk(a,b,c);
    printf("%s\n",a);
}
