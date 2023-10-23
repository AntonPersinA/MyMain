#include <time.h>
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


void swap_value_or(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


void insertion_sort(int *mas, int len_mas){
    for (int i = 1; i < len_mas; ++i) {
        for (int j = i; j>0;--j){
            if (*(mas + j) < *(mas + j - 1)){
                swap_value_or(mas+j, mas + j - 1);
            }
        }
    }
}


void q_sort(int *mas, int len){
    if (len>9){                                     //Оптимальное значение тут 3
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
        insertion_sort(mas,len);
    }
}


int compare_array(int *mas1, int *mas2, int len){
    for (int i = 0; i < len; ++i){
        if (*(mas1 + i) != *(mas2 + i))return 0;
    }
    return 1;
}


int test_q_sort(){
    FILE *fr = fopen("3test1.txt", "r");

    if (fr == NULL){
        perror("3test1.txt");
        return 0;
    }
    int len;
    fscanf(fr, "%d", &len);

    int *test_mas = malloc(sizeof (int)*len);
    if(test_mas == NULL){fclose(fr);return 0;}
    int *ans_mas = malloc(sizeof (int)*len);
    if(ans_mas == NULL){fclose(fr);return 0;}

    for(int i = 0; i<len;++i){
        fscanf(fr, "%d", test_mas+i);
    }
    for(int i = 0; i<len;++i){
        fscanf(fr, "%d", ans_mas+i);
    }

    q_sort(test_mas, len);
    if(compare_array(test_mas, ans_mas, len)){
        fclose(fr);
        return 1;
    }
    fclose(fr);
    return 0;
}


int main() {
    int *mas = malloc(sizeof(int)*size);
    fill_mas_rand(mas, size, 10);
    print_array(mas, size);

    printf("\n");
    q_sort(mas, size);
    print_array(mas, size);


    free(mas);

    printf("\ntest = %d\n", test_q_sort());
    return 0;
}