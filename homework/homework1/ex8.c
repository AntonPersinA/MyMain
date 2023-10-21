#include <stdlib.h>
#include <stdio.h>

#define size    10


void print_array(int *mas, int length){
    printf("{");
    for (int i = 0; i<length; i++){
        printf("%d, ", mas[i]);
    }
    printf("\b\b}\n");
}


void swap_value_or(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


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


int main(){
    int mas[size] = {1,2,3,4,5};
    array_reverse(mas, 1,3);
    print_array(mas, size);
    return 0;
}