#include <stdlib.h>
#include <stdio.h>

int remainder1(int divider, int denominator) {
    if (!denominator) {
        printf("ZeroDivisionError: integer division or modulo by zero");
        return 0;
    }
    if (denominator == -1 || denominator == 1) {
        return 0;
    }
    else {
        if (divider > 0 && denominator > 0) {
            while (divider >= denominator) {
                divider -= denominator;
            }
            return divider;
        }
        if (divider < 0 && denominator > 0) {
            while (divider < 0) {
                divider += denominator;
            }
            return divider;
        }
        if (divider < 0 && denominator < 0) {
            while (divider <= denominator) {
                divider -= denominator;
            }
            return divider;
        }
        if (divider > 0 && denominator < 0) {
            while (divider>0) {
                divider += denominator;
            }
            return divider;
        }
    }
}


int test_remainder() {
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL){
        perror("1test1.txt");
        return 0;
    }

    int a, b, c, count_test;

    fscanf(fr, "%d", &count_test);

    for (int i = 0; i < count_test; ++i) {
        fscanf(fr, "%d %d %d", &a, &b, &c);

        if (remainder1(a, b) != c){
            printf("%d %d %d", a, b, remainder1(a, b));
            fclose(fr);
            return 0;
        }
    }
    fclose(fr);
    return 1;
}

int main() {
    printf("\n%d\n", test_remainder());
    return 0;
}