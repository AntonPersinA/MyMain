#include <stdlib.h>
#include <stdio.h>

#define size    10

int array_zero(int *mas, size_t len_mas) {
    int i, count_zero = 0, h;
    for (i = 0; i < len_mas; ++i) {
        if (mas[i] == 0) {
            count_zero++;
        }
    }
    return count_zero;
}


void main(){
    int *mas = malloc(sizeof(int)*size);
    int answer = array_zero(mas, size);
    printf("answer = %d\n", answer);
}