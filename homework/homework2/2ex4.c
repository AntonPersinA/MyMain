#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define size    10

void swap_value_or(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


void print_array(int *mas, int length){
    printf("{");
    for (int i = 0; i<length; i++){
        printf("%d, ", mas[i]);
    }
    printf("\b\b}\n");
}


//Переменная limit ставит предел генерируемого значения, если стоит ноль, то limit определяется функцией rand()
void fill_mas_rand(int*mas, int len, int limit) {
    srand(clock());
    if (limit) {
        limit++;
        for (int i = 0; i < len; i++)
            *(mas + i) = rand() % (limit);
    }
    else{
        limit++;
        for (int i = 0; i < len; i++)
            *(mas + i) = rand();
    }
}


void sort_depend_first(int *mas, int len) {
    int place_first = len-1, i = 0;
    swap_value_or(mas,(mas+place_first));
    while(place_first>1 && place_first >= i+1){
        while (*(mas+place_first)<=*(mas+place_first-1) && place_first!=0){
            swap_value_or(mas+place_first-1,(mas+place_first));
            place_first--;
        }
        while (i<place_first){
            if (*(mas+i)>=*(mas+place_first)){
                swap_value_or((mas+i),(mas+place_first-1));
                swap_value_or((mas+place_first),(mas+place_first-1));
                place_first--;
                break;
            }
            i++;
        }
    }
}



int main() {
    int *mas = malloc(sizeof(int)*size);
    fill_mas_rand(mas, size, 10);
    print_array(mas, size);

    printf("\n");

    sort_depend_first(mas, size);
    print_array(mas, size);

    free(mas);
    return 0;
}