#include <stdio.h>

void swap_value(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


int main(){
    int x = 10, y = 5;
    printf("x = %d, y = %d\n", x, y);
    swap_value(&x, &y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}