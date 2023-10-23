#include <stdio.h>
#include <math.h>

int parenthesis_rule(char *stroka) {
    int skobe = 0, i = 0;
    while (*(stroka+i) != *"\0") {
        if (*(stroka+i) == *"(" || *(stroka+i) == *"[" || *(stroka+i) == *"{"){
            skobe++;
        }
        if (*(stroka+i) == *")" || *(stroka+i) == *"]" || *(stroka+i) == *"}"){
            skobe--;
            if (skobe <0)
                return 0;
        }
        ++i;
    }
    return !skobe;
}


int test_scobe_rule() {
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL){
        perror("1test1.txt");
        return 0;
    }

    int count_test, flag;
    char *str;
    fscanf(fr, "%d", &count_test);

    for (int i = 0; i < count_test; ++i) {
        fscanf(fr, "%d %s", &flag, str);

        if (parenthesis_rule(str) != flag){
            printf("%s", str);
            fclose(fr);
            return 0;
        }
    }
    fclose(fr);
    return 1;
}


int main(){
    printf("%d\n", test_scobe_rule());
    return 0;
}