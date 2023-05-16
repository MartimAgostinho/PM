#include <stdio.h>

#define MAXWORDLENGHT 1000

struct test{

    int  a;
    int  b;
    char c[5];
};

void add_str(char *fstr,char *str1,char *str2){

    int i,n;

    for(i = 0;str1[i] != '\0';i++){ fstr[i] = str1[i]; }
    for(n = 0;str2[n] != '\0';n++){ fstr[i + n] = str2[n]; }

}
void printtest(struct test tt){

    printf("%d\n%d\n%s\n",tt.a,tt.b,tt.c);
}



int main(){
 
    char *str1 = "pica";
    char *str2 = "dont eat that";
    char fstrp[10000];

    add_str(fstrp, str1, " ");

    add_str(fstrp, fstrp, str2);
    printf("%s\n",fstrp);
    /*
    FILE *fp;
    int nr = 69,nr1;
    struct test tt = {
        .a = 0,
        .b = 5,
        .c = "pixa"
    },rwar;

    fp = fopen("test.bin", "wb");
    printtest(tt);
    
    fwrite(&tt, sizeof(struct test), 1, fp);
    fwrite(&nr, sizeof(int), 1, fp);

    fclose(fp);
    fp = fopen("test.bin", "rb");
    fread(&rwar, sizeof(struct test), 1, fp);
    fread(&nr1,sizeof(int),1,fp);
    printtest(rwar);
    printf("\nAAA:%d\n",nr1);
    fclose(fp);*/
    return 0;
}
