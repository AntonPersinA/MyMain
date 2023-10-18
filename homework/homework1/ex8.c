#include <stdlib.h>
#include <stdio.h>

int *array_reverse(int *mas, int a, int b){
    int help = 0;
    for (a; a<b; a++) {
        if (a >= b-help){
            return mas;
        }
        swap_value_or((mas + a), (mas + b - help));
        help+=1;
    }
    return mas;
}


void main(){
    int *mas = malloc(sizeof(int)*size);
    int answer = array_zero(mas, size);
    printf("answer = %d\n", answer);
}