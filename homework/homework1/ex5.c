#include <stdio.h>

int parenthesis_rule(char *stroka) {
    int skobe = 0, i = 0;
    while (*(stroka+i) != *"\0") {
        if (*(stroka+i) == *"(" || *(stroka+i) == *"[" || *(stroka+i) == *"{"){
            skobe++;
        }
        if (*(stroka+i) == *")" || *(stroka+i) == *"]" || *(stroka+i) == *"}"){
            skobe--;
            if (skobe <0)
                return 0;
        }
        ++i;
    }
    return !skobe;
}


void main(){
    char *string = "(Hello)(world)";
    int answer = parenthesis_rule(string);
    printf("answer = %d\n", answer);
}