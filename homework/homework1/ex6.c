#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void print_array(int *mas, int length){
    printf("{");
    for (int i = 0; i<length; i++){
        printf("%d, ", mas[i]);
    }
    printf("\b\b}\n");
}


int is_it_prime(int num){
    num = abs(num);
    if (num <=1)
        return 0;
    int i;
    double power = pow((float)num, 0.5);
    for (i = 2; i<=power*1; ++i){
        if (num%i==0){
            return 0;
        }
    }
    return 1;
}


void print_prime_before(int num_before){
    num_before = abs(num_before);
    printf("{");
    for (int i = 2; i<=num_before; ++i){
        if (is_it_prime(i) == 1){
            printf("%d, ", i);
        }
    }
    printf("\b\b}");
}


int test_prime_before(){
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL){
        perror("1test1.txt");
        return 0;
    }

    int count;
    fscanf(fr, " %d", &count);
    int *mas = malloc(sizeof(int)*count);
    for(int i = 0; i<count; ++i){
        fscanf(fr, "%d", (mas + i));
    }
    print_prime_before(*(mas + count - 1));
    printf("\n");
    print_array(mas, count);
    fclose(fr);
    free(mas);
}
int main(){
    test_prime_before();
    return 0;
}