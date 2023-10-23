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


int test_luck_ticket(){
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL) {
        perror("1test1.txt");
        return 0;
    }
    int answeing;

    fscanf(fr, "%d", &answeing);
    return answeing==luck_ticket();
}


int main(){
    int answer = luck_ticket();
    printf("answer = %d\n", answer);

    printf("test_check = %d\n", test_luck_ticket());
    return 0;
}