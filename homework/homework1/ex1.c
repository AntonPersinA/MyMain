#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void swap_value(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


int test_swap(){
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL){
        perror("1test1.txt");
        return 0;
    }

    int a_test, b_test;
    fscanf(fr, "%d %d", &a_test, &b_test);
    int a = a_test, b = b_test;

    fscanf(fr, "%d %d", &a_test, &b_test);
    swap_value(&a, &b);
    fclose(fr);
    if (a == a_test && b == b_test){
        return 1;
    }
    return 0;
}



int main(){
    printf("%d\n", test_swap());
    return 0;
}