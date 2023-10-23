#include <stdlib.h>
#include <stdio.h>


int array_zero(int *mas, size_t len_mas) {
    int i, count_zero = 0;
    for (i = 0; i < len_mas; ++i) {
        if (mas[i] == 0) {
            count_zero++;
        }
    }
    return count_zero;
}


int test_zero() {
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL){
        perror("1test1.txt");
        return 0;
    }

    int a, count_zero_ans, len_mas;

    fscanf(fr, "%d %d", &count_zero_ans, &len_mas);
    int *mas = malloc(sizeof(int)*len_mas);
    for (int i = 0; i < len_mas; ++i) {
        fscanf(fr, "%d", &a);

        mas[i] = a;
    }

    if (array_zero(mas, len_mas) == count_zero_ans){
        free(mas);
        fclose(fr);
        return 1;
    }
    fclose(fr);
    free(mas);
    return 0;
}


int main() {
    printf("%d\n", test_zero());
    return 0;
}