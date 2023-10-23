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
    b--;
    for (a; a<b; a++) {
        if (a >= b-help){
            return mas;
        }
        swap_value_or((mas + a), (mas + b - help));
        help+=1;
    }
    return mas;
}


int compare_array(int *mas1, int *mas2, int len){
    for (int i = 0; i < len; ++i){
        if (*(mas1 + i) != *(mas2 + i))return 0;
    }
    return 1;
}


int test_reverse(){
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL) {
        perror("1test1.txt");
        return 0;
    }

    int x1,x2;
    fscanf(fr, "%d", &x1);
    fscanf(fr, "%d", &x2);

    int len;
    fscanf(fr, "%d", &len);

    int *mas_in = malloc(sizeof(int)*len);
    int *mas_answer = malloc(sizeof(int)*len);


    int in;
    for (int i = 0; i<len;++i){
        fscanf(fr, "%d", &in);
        *(mas_in+i) = in;
    }

    for (int i = 0; i<len;++i){
        fscanf(fr, "%d", &in);
        *(mas_answer+i) = in;
    }

    array_reverse(mas_in,x1,x2+1);

    int answer_test = compare_array(mas_in, mas_answer, len);
    free(mas_in);
    free(mas_answer);
    fclose(fr);
    return answer_test;
}

int main(){
    printf("%d\n", test_reverse());
    return 0;
}