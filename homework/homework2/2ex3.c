#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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


//Переменная limit ставит предел генерируемого значения, если стоит ноль, то limit определяется функцией rand()
void fill_mas_rand(int*mas, int len, int limit){
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


//На массиве из 100'000 элементов рабоает 18.5/19.7/20.4 секунды
void *buble_sort(int *mas, int len, char if1down){
    if (if1down) {
        for (int i = len - 2; i >= 0; i--) {
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) >= (*(mas + g - 1)))
                    swap_value_or((mas + g), (mas + g - 1));
                else break;
            }
        }
    }
    else{
        for (int i = len - 2; i >= 0; i--) {
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) <= (*(mas + g - 1)))
                    swap_value_or((mas + g), (mas + g - 1));
                else break;
            }
        }
    }
}


//На массиве из 100'000 элементов при лимите значений равным 100 рабоает 0.002198/0.008769, если лимит обозначен как максимум функции rand(), то секунд 6.038236/6.277364
void counting_sort(int *mas, size_t len_mas){
    int min_el = 0, max_el = 0;
    for (int i = 0; i < len_mas; ++i){
        if (*(mas + i) > max_el)max_el = *(mas + i);
        if (*(mas + i) < min_el)min_el = *(mas + i);
    }

    if (min_el >= 0) {
        int *help_plus = calloc(max_el+1, sizeof(int));
        if (help_plus == NULL){printf("error malloc");return;}
        for (int i = 0; i < len_mas; ++i) {
            *(help_plus + *(mas + i)) += 1;
        }
        int mas_now = 0;
        for (int i = 0; i <= max_el; ++i){
            for (int g = 0; g < *(help_plus + i); ++g) {
                *(mas + mas_now) = i;
                mas_now++;
            }
        }
        free(help_plus);
    }
    else{
        int *help_plus = calloc(max_el+1, sizeof(int));
        int *help_minus = calloc(-min_el+1, sizeof(int));
        if (help_plus == NULL){printf("error help_plus malloc");return;}
        if (help_minus == NULL){printf("error help_minus malloc");return;}
        for (int i = 0; i < len_mas; ++i) {
            if (*(mas + i) >= 0) {
                *(help_plus + *(mas + i)) += 1;
            }
            else{
                *(help_minus - *(mas + i)) += 1;
            }
        }
        int mas_now = 0;
        print_array(help_minus, -min_el+1);
        for (int i = -min_el; i >= 1; +--i){
            for (int g = 0; g < *(help_minus+i); ++g) {
                *(mas + mas_now) = -i;
                mas_now++;
                printf("mas_now = %d\n", mas_now);
            }
        }
        printf("mas_now = %d\n ", mas_now);
        for (int i = 1; i <= max_el; ++i){
            for (int g = 0; g < *(help_plus + i); ++g) {
                *(mas + mas_now) = i;
                mas_now++;
            }
        }
        free(help_plus);
        free(help_minus);
    }
}


#define size    100000
#define fill_limit    100


int main() {
    clock_t start, end;

    int *mas = malloc(sizeof(int)*size);
    fill_mas_rand(mas, size, fill_limit);
//    print_array(mas,size);
    start = clock();
    buble_sort(mas, size, 0);
    end = clock();
//    print_array(mas,size);
    printf("buble sort time = %f\n", ((float)(end - start))/CLOCKS_PER_SEC);

    printf("\n");

    fill_mas_rand(mas, size, fill_limit);
//    print_array(mas,size);
    start = clock();
    counting_sort(mas, size);
    end = clock();
//    print_array(mas,size);
    printf("counting sort time = %f\n", ((float)(end - start))/CLOCKS_PER_SEC);

    free(mas);
    return 0;
}