#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

//function prototypes
string scan(FILE*);
int colNum(char x);

int main(int argc, char *argv[]){

    FILE *fp = fopen(argv[1], "r");

    vector<string> tokenVect;

    while(!feof(fp)){

        string token = scan(fp);

        if(token == "error"){
            cout << token << endl;
            exit(0);
        }

        else{
            tokenVect.push_back(token);
        }

    }

    //print elements of tokenVect
    cout << '{';
    for(int i = 0; i < tokenVect.size(); i++){
        
        
        if(i != tokenVect.size() - 1){
            cout << tokenVect.at(i) << ", ";
        }
        else {
            cout << tokenVect.at(i);
        }
        

    }
    cout << '}';

    return 0;
}

string scan(FILE* fp){

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

    string stateToken[] = {
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
    int state = 1, lastState;
    string word;

    do{

        //get input character
        x = fgetc(fp);

        //get correct column number for the input character
        int num = colNum(x);
        
        //store last instance of state
        lastState = state;
        
        //longest possible token rule; exhaust possible input in a state
        if(transitionTable[state][num] != 0) {

            //update state based on the transitionTable
            state = transitionTable[state][num];

            if(state == 16){
            //append the char into the word
            word.push_back(x);
            }

        }
        else{
            //2 possibilities: invalid state, recognized state
            //invalid token
            if(stateToken[state] == "error"){
                return "error";
            }
            //recognized state
            //2 possibilities: tokenless state or valid token
            else {
                //tokenless state
                if(stateToken[lastState] == "error"){
                    return "error";
                }
                else if(word == "read"){
                    return "read";
                }
                else if(word == "write"){
                    return "write";
                }
                //valid token
                else{
                    return stateToken[lastState];
                }

                word.clear();
                
                //goes back to the first state
                state = 1;

                //go to the last instance
                ungetc(x, fp);

            }

        }

    }while(true);

    return "error";
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