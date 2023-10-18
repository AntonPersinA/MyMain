#include <stdlib.h>
#include <stdio.h>

int sum_num(int num) {
    int count = 0;
    num = abs(num);
    while (num) {
        count += num % 10;
        num /= 10;
    }
    return count;
}


int luck_ticket() {
    int mas[27] = {0}, i, count = 0;
    for (i = 0; i < 1000; ++i) {
        mas[sum_num(i)] += 1;
    }
    for (i = 0; i <= (sizeof(mas) / sizeof(mas[0])) / 2; ++i)
        count += mas[i] * mas[i];
    return count * 2;
}


void main(){
    int answer = luck_ticket();
    printf("answer = %d\n", answer);
}