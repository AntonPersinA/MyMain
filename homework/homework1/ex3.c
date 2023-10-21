#include <stdlib.h>
#include <stdio.h>

int remainder1(int divider, int denominator) {
    if (!denominator) {
        return -1;
    } else {
        denominator = abs(denominator);
        divider = abs(divider);
        while (divider >= denominator) {
            divider -= denominator;
        }
        return divider;
    }
}


int main(){
    int number1 = 21, number2 = 5;
    int answer = remainder1(number1, number2);
    printf("answer = %d\n", answer);
    return 0;
}