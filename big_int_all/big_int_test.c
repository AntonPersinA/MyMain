//
// Created by anton on 27.10.23.
//
#include <string.h>
#include "big_int/big_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_BINARY_LENGTH 900000
#define const1 100

void big_int_test_add(){
    int sig = system("python3 big_int_sum1.py");
    clock_t start_time, end_time;
    double total_time;
    start_time = clock();
    FILE *file = fopen("big_int_test.txt", "r");
    char *binary = malloc(MAX_BINARY_LENGTH + 1);
    char *buffer = malloc(MAX_BINARY_LENGTH + 1);
//    int err = 0;
    for (long i = 0; i < 300*300; i++) {
        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n1 = big_int_get(binary);
//        big_int_all *n12 = big_int_copy(n1);

        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *n2 = big_int_get(binary);

        buffer=fgets(buffer, MAX_BINARY_LENGTH + 1, file);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        strcpy(binary, buffer);
        big_int *ans = big_int_get(binary);

        big_int *n3 = big_int_add1(n1, n2);
//        big_int_add2(n12, n2);
        if ((!big_int_equal(ans, n3))) {                              // || (!big_int_equal(ans, n12))
            printf("////////////////////////IMPOSTER IN ADD i=%li//////////////\n", i*3+1);
//            printf("n1 = ");
//            big_int_print(n1);
//            printf("n2 = ");
//            big_int_print(n2);
//            printf("n3 = ");
//            big_int_print(n3);
//            printf("an = ");
//            big_int_print(ans);
//            err = 1;
            break;
        }

        big_int_free(n1);
        big_int_free(n2);
        big_int_free(ans);
//        big_int_free(n12);
        big_int_free(n3);

    }
    free(binary); // Освобождаем память
    free(buffer);
    fclose(file); // Закрываем файл
    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения add : %f секунд\n", total_time);
//    return err;
}