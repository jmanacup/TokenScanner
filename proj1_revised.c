#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


const char* scan(FILE*);
int colNum(char x);

int main(int argc, char *argv[]){

    FILE *fp = fopen(argv[1], "r"); 


    printf("%s", scan(fp));

    return 0;
}

const char* scan(FILE* fp){

    int transitionTable[17][15] = {
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,1, 1, 2, 10, 6, 7, 8, 9, 11, 0, 13, 14, 16, 0},
     {0, 0, 0, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
     {0, 4, 4, 4, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
     {0, 4, 4, 1, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,12,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,15,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,15,14,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,15,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,16,16,0}
    };

    static char* stateToken[] = {
        "error",
        "error",
        "div",
        "error",
        "error",
        "error",
        "lparen",
        "rparen",
        "plus",
        "minus",
        "times",
        "error",
        "assign",
        "error",
        "number",
        "number",
        "id"
        };

    char x;
    int state = 1, index = 0, lastState;
    char word[100];

    //used to store the tokens
    char listToken[500][100];

    do{
        x = fgetc(fp);

        //get correct column number
        int num = colNum(x);
        
        lastState = state;
        
        //longest possible token rule; exhaust possible input in a state
        if(transitionTable[state][num] != 0) {

            //update state based on the transitionTable
            state = transitionTable[state][num];

            if(state == 16){
            //append the char into the word
            word[index++] = x;
            }

        }
        else{
            //2 possibilities: invalid state, recognized state
            //not a valid token
            if(strcmp(stateToken[state], "error") == 0){
                printf("%s", "error.");
                exit(0);
            }
            //recognize state
            //2 possibilities: recognized but not valid and valid
            else {
                if(strcmp(stateToken[lastState], "error") == 0){
                    return "error.";
                }
                else if(strcmp(word, "read") == 0){
                    return "read";
                }
                else if(strcmp(word, "write") == 0){
                    return "write";
                }
                else{
                    return stateToken[lastState];
                }

                index = 0;

                memset(word, 0, sizeof(word));

                state = 1;

                //go to the last instance
                ungetc(x, fp);

            }

        }

    }while(x != EOF);
}

int colNum(char x){
    
    int col;

    if(x == '\n'){
        col = 2;
    }
    else if(isspace(x)){
        col = 1;
    }
    else if(isdigit(x)){
        col = 12;
    }
    else if(isalpha(x)){
        col = 13;
    }
    else{
        switch(x){
            case '/':
                col = 3;
                break;
            case '*':
                col = 4;
                break;
            case '(':
                col = 5;
                break;
            case ')':
                col = 6;
                break;
            case '+':
                col = 7;
                break;
            case '-':
                col = 8;
                break;
            case ':':
                col = 9;
                break;
            case '=':
                col = 10;
                break;
            case '.':
                col = 11;
                break;
            default:
                col = 14;  
        }
    }
    return col;

}