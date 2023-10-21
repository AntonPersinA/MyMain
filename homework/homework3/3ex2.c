#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>


void swap_value_or(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


int min(int a, int b){
    if (a>b)return b;
    return a;
}


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


void print_array(int *mas, int length){
    printf("{");
    for (int i = 0; i<length; i++){
        printf("%d, ", mas[i]);
    }
    printf("\b\b}\n");
}


char el_in_sort_mas(int *mas, size_t len_mas, int element){

    if ( len_mas < 4){
        for (int i = 0; i < len_mas; ++i){
            if (element == *(mas + i)){
                return 1;
            }
        }
        return 0;
    }
    if (element < *(mas + len_mas/2)){
        return el_in_sort_mas(mas, len_mas/2, element);
    }
    return el_in_sort_mas(mas + len_mas/2, len_mas - len_mas/2, element);
}


void *selection_sort(int * mas, int len, char if1down){
    int lower_i;
    if (!if1down) {
        for (int i = 0; i <= len - 2; i++) {
            lower_i = i;
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) < *(mas + lower_i)) lower_i = g;
            }
            if (lower_i != i) {
                swap_value_or((mas + i), (mas + lower_i));
            }
        }
    }
    else{
        for (int i = 0; i <= len - 2; i++) {
            lower_i = i;
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) > *(mas + lower_i)) lower_i = g;
            }
            if (lower_i != i) {
                swap_value_or((mas + i), (mas + lower_i));
            }
        }
    }
}


void q_sort(int *mas, int len){
    if (len>3){                                     //Оптимальное значение тут 3
        int *main_i, *start = mas, *end = mas + len - 1;
        if (*mas >= *(mas + len - 1) && *mas <= *(mas + len/2) || *mas <= *(mas + len - 1) && *mas >= *(mas + len/2) ){
            main_i = mas;
        }
        else if (*(mas + len - 1) >= *mas && *(mas + len - 1) <= *(mas + len/2) || *(mas + len - 1) <= *mas && *(mas + len - 1) >= *(mas + len/2)){
            main_i = (mas + len -1);
        }
        else{
            main_i = (mas + len/2);
        }
        while(1) {
            while (*(start) <= *(main_i) && start <= mas + len - 1) {
                ++start;
                if (start > end) {
                    start--;
                    break;
                }
            }
            while (*(end) > *(main_i) && end >= mas) {
                --end;
            }
            if (start < end){
                swap_value_or(start, end);
                if(main_i == end){
                    main_i = start;
                }
                else if (main_i == start){
                    main_i = end;
                }
            }
            else {
                swap_value_or(end, main_i);
                main_i = end;
                break;
            }
        }
        int *main_help = main_i;
        int len_im = 0;
        for(; main_i >mas;main_i--, len_im++){ }
        q_sort(main_help + 1, len - len_im - 1);
        q_sort(mas, len_im);
    }
    else{
        selection_sort(mas,len,0);
    }
}


int matching_elements(int *masn, size_t len_masn,
                       int *mask, size_t len_mask,
                       int *mas_new, int len_mas_new){
    q_sort(masn, len_masn);
    int k = 0, new = 0;
    while(1){
        while (k<len_mask){
            if(el_in_sort_mas(masn, len_masn, *(mask + k))){
                *(mas_new + new) = *(mask + k);
                new++;
                if (new == len_mas_new){
                    return new;
                }
            }
            k++;
        }
        if (!new){
            return new;
        }
        return new;
    }
}


int main() {
    int n,k;
    printf("Enter one number(for n): ");
    scanf("%d", &n);
    printf("Enter one number(for k): ");
    scanf("%d", &k);

    int len_answer = min(n,k);
    int *mas_n = malloc(sizeof(int) * n);
    fill_mas_rand(mas_n, n, 10);
    int *mas_k = malloc(sizeof(int) * k);
    fill_mas_rand(mas_k, k, 10);

    int *mas_answer = malloc(sizeof(int) * len_answer);

    printf("mas_n = ");
    print_array(mas_n, n);
    printf("mas_k = ");
    print_array(mas_k, k);

    int flag = matching_elements(mas_n, n, mas_k, k, mas_answer, len_answer);

    if(flag){
        printf("mas_answer = ");
        print_array(mas_answer, flag);
    }
    else{
        printf("Совпадений нет\n");
    }
}