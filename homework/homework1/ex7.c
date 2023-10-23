#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_in_str(char *stroka1, char *stroka2) {
    if (strlen(stroka1) > strlen(stroka2) || (*stroka2 == *"") || (*stroka1 == *""))
        return 0;
    int i, g, flag, count = 0;
    for (g = 0; g <= strlen(stroka2) - strlen(stroka1); ++g) {
        flag = 1;
        for (i = 0; i < (strlen(stroka1)); ++i) {
            if (*(stroka1 + i) != *(stroka2 + g + i)) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            count++;
        }
    }
    return count;
}

int test_str_in_str() {
    FILE *fr = fopen("1test1.txt", "r");

    if (fr == NULL) {
        perror("1test1.txt");
        return 0;
    }

    char *str2;
    char *str1;
    int str2_len;
    int str1_len;
    int answering;

    fscanf(fr, "%d", &str1_len);

    str1 = malloc(str1_len);
    if (str1 == NULL){fclose(fr);return -2;}
    fscanf(fr, "%s", str1);


    fscanf(fr, "%d", &str2_len);

    str2 = malloc(str2_len);
    if (str1 == NULL) {fclose(fr);return -2;}
    fscanf(fr, "%s", str2);

    fscanf(fr, "%d", &answering);

    if (answering != str_in_str(str2, str1)) {
        free(str1);
        free(str2);
        fclose(fr);
        return 0;
    }


    free(str1);
    free(str2);
    fclose(fr);
    return 1;
}

int main() {
    printf("%d\n", test_str_in_str());
    return 0;
}