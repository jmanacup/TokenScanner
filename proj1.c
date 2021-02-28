#include <stdio.h>
#include <ctype.h>


void scanner(FILE*);

int main(int argc, char *argv[]){

    FILE *fp = fopen(argv[1], "r" ); 

    if(fp == 0)
        printf("%s", "File cannot be opened");

    else{

        scanner(fp);
        
    }
    return 0;
}

void scanner(FILE* fp){

    char x;

    do{
        x = fgetc(fp);

        if(isalpha(x)){
            printf("%c", x);
        }


    }while(x != EOF);

}