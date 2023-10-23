#include <stdlib.h>
#include <stdio.h>


void swap_value_or(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
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


int more_meet_el(int *mas, size_t len_mas){
    if (len_mas == 1)return *mas;
    int *help_mas = malloc(len_mas*sizeof(int));
    for (int i = 0; i < len_mas; ++i){
        help_mas[i] = mas[i];
    }
    q_sort(help_mas, len_mas);
    int kolv_el_max = 1, kolv_el_now = 1, ind_max_el = 0;
    for (int i = 1; i < len_mas; ++i){
        if (*(help_mas+i)==*(help_mas+i-1)){
            kolv_el_now++;
            ind_max_el = kolv_el_max>kolv_el_now?ind_max_el:i-1;
            kolv_el_max = kolv_el_max>kolv_el_now?kolv_el_max:kolv_el_now;
        }
        else{
            kolv_el_now =1;
        }
    }
    int g = *(help_mas + ind_max_el);
    free(help_mas);
    return g;
}

int test_more_meet_el(){

}


int main() {
    int mas[5] = {2,1,3,3,2};
    printf("%d\n", more_meet_el(mas, 5));
}