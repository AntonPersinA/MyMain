#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>




int compare_array(int *mas1, int *mas2, int len){
    for (int i = 0; i < len; ++i){
        if (*(mas1 + i) != *(mas2 + i))return 0;
    }
    return 1;
}


//Функция принимает в себя и число1 и число2, она возвращает, есть ли значащий бит на месте числа2 в числе1
int value_num_byte(int start_value, int count) {
    int help_number = 1, i;
    for (i = 1; i <= count - 1; i++) {
        help_number = help_number << 1;
    }
    help_number = help_number & start_value;
    if (help_number >= 1) {
        help_number = 1;
    }
    return help_number;
}


int min(int a, int b){
    if (a>b)return b;
    return a;
}


//Задание первое(1) //В вводе ставить ссылку на переменные --- &
void swap_value_or(int *number1, int *number2) {
    if (number1!=number2) {
        *number1 ^= *number2;
        *number2 ^= *number1;
        *number1 ^= *number2;
    }
}


//Задание первое(1) //В вводе ставить ссылку на переменные --- &
void swap_value_math(int *num1, int *num2) {
    if (num1!=num2) {
        *num1 = *num1 - *num2;
        *num2 = *num1 + *num2;
        *num1 = *num2 - *num1;
    }
}


//Задание второе(2)
int array_zero(int *mas, size_t len) {
    int i, count_zero = 0;
    for (i = 0; i < len; i++) {
        if (mas[i] == 0) {
            count_zero++;
        }
    }
    return count_zero;
}


//Задание третье(3)
int remainder1(int divider, int denominator) {
    if (!denominator) {
        return -1;
    } else {
        denominator = abs(denominator);
        divider = abs(divider);
        while (divider >= denominator) {
            divider -= denominator;
        }
        return divider;
    }
}


int len_num(int num) {
    int i = 10, count = 1;
    num = abs(num);
    while (i <= num) {
        count++;
        i *= 10;
    }
    return count;
}


int sum_num(int num) {
    int count = 0;
    num = abs(num);
    while (num) {
        count += num % 10;
        num /= 10;
    }
    return count;
}


//Задание четыре(4)
int luck_ticket() {
    int mas[27] = {0}, i, count = 0;
    for (i = 0; i < 1000; i++) {
        mas[sum_num(i)] += 1;
    }
    for (i = 0; i <= (sizeof(mas) / sizeof(mas[0])) / 2; i++)
        count += mas[i] * mas[i];
    return count * 2;
}


//Задание пять(5)
int parenthesis_rule(char *stroka) {
    int answer = 1, skobe = 0, i = 0;
    char k = *stroka;
//    printf("%d", *(stroka+3)==*("l"));
    while (*(stroka+i) != *"\0") {
        if (*(stroka+i) == *"(" || *(stroka+i) == *"[" || *(stroka+i) == *"{"){
            skobe++;
        }
        if (*(stroka+i) == *")" || *(stroka+i) == *"]" || *(stroka+i) == *"}"){
            skobe--;
            if (skobe <0)
                return 1;
        }
//        printf("%c,        %d\n", stroka[i], skobe);
        i++;
    }
    return 1;
}


int is_it_prime(int num){
    num = abs(num);
    if (num <=1)
        return 0;
    int i;
    double power = pow(num*1.0, 0.5);
    for (i = 2; i<=power*1; i++){
        if (num%i==0){
            return 0;
        }
    }
    return 1;
}


//Задание шесть(6)
void print_prime_before(int num_before){
    num_before = abs(num_before);
    printf("{");
    for (int i = 2; i<=num_before; i++){
        if (is_it_prime(i) == 1){
            printf("%d, ", i);
        }
    }
    printf("\b\b}");
}


//Задание семь(7)
int str_in_str(char *stroka1, char *stroka2){
    if (strlen(stroka1)> strlen(stroka2) || (*stroka2 == *"") || (*stroka1 == *""))
        return 0;
    int i,g, flag, count = 0, len1 = (strlen(stroka1));
    for (g = 0; g<strlen(stroka2)-strlen(stroka1); g++){
        flag = 1;
        for (i = 0; i < len1;i++){
            if (*(stroka1+i) != *(stroka2+g+i)){
                flag = 0;
                break;
            }
        }
        if (flag){
            count++;
        }
    }
    return count;
}


void print_array(int *mas, int length){
    printf("{");
    for (int i = 0; i<length; i++){
        printf("%d, ", mas[i]);
    }
    printf("\b\b}\n");
}


//Задание восемь(8)                 На вход массив и по индексам та его часть, которую надо перевернуть
int *array_reverse(int *mas, int a, int b){
    int help = 0;
    for (a; a<b; a++) {
        if (a >= b-help){
            return mas;
        }
        swap_value_or((mas + a), (mas + b - help));
        help+=1;
    }
    return mas;
}


//Д\З два(2). Задание 1:После 40 числа рекурсия работает как минимум на сукунду дольше цикла
long long fibonachi_def(int n){
    if (n==1 || n == 2)
        return 1;
//    if (n%2 == 0){
//        long long f_k = fibonachi_def(n/2);
//        long long f_k1 = fibonachi_def(n/2-1);
//        return f_k*(2*f_k1 + f_k);
//    }
    return fibonachi_def(n-1)+ fibonachi_def(n-2);
}


long long fibonachi_for(int n){
    long long s_1 = 1, s_2 = 1, help;
    for (int i = 3; i <= n; i++){
        help = s_2;
        s_2 += s_1;
        s_1 = help;
    }
    return s_2;
}


//Д/З два(2). Задание 2.
long long int_pow_n(long long m, long long n){
    long long ans = 1;
    for(int i = 0; i<n;i++)
        ans*=m;
    return ans;
}


long long int_pow_logn(long long m, long long n){
    long long otv = 1;
    while (n>1){
        if (n%2 == 0){
            m*=m;
            n>>=1;
        }
        else{
            otv*=m;
            n-=1;
            m*=m;
            n>>=1;
        }
    }
    return otv*m;
}


//Д/З два(2). Задание 3. На массиве из 100'000 элементов рабоает 18.5/19.7/20.4 секунды
void *buble_sort(int *mas, int len, char if1down){
    if (if1down) {
        for (int i = len - 2; i >= 0; i--) {
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) >= (*(mas + g - 1)))
                    swap_value_or((mas + g), (mas + g - 1));
                else break;
            }
        }
    }
    else{
        for (int i = len - 2; i >= 0; i--) {
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) <= (*(mas + g - 1)))
                    swap_value_or((mas + g), (mas + g - 1));
                else break;
            }
        }
    }
}


//Д/З два(2). Задание 3. На массиве из 100'000 элементов рабоает 12.1/12.3/12.1 секунд
void *selection_sort(int * mas, int len, char if1down){
    int lower_i;
    if (!if1down) {
        for (int i = 0; i <= len - 2; i++) {
            lower_i = i;
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) < *(mas + lower_i)) lower_i = g;
            }
            if (lower_i != i) {
                swap_value_or((mas + i), (mas + lower_i));
            }
        }
    }
    else{
        for (int i = 0; i <= len - 2; i++) {
            lower_i = i;
            for (int g = i + 1; g < len; g++) {
                if (*(mas + g) > *(mas + lower_i)) lower_i = g;
            }
            if (lower_i != i) {
                swap_value_or((mas + i), (mas + lower_i));
            }
        }
    }
}


void fill_mas_rand(int*mas, int len, int limit){
    srand(clock());
    if (limit) {
        limit++;
        for (int i = 0; i < len; i++)
            *(mas + i) = rand() % (limit);
    }
    else{
        limit++;
        for (int i = 0; i < len; i++)
            *(mas + i) = rand();
    }
}


void sort_depend_first(int *mas, int len){
    int place_first = len-1, i = 0;
    swap_value_or(mas,(mas+place_first));
    while(place_first>1 && place_first >= i+1){
        while (*(mas+place_first)<=*(mas+place_first-1) && place_first!=0){
            swap_value_or(mas+place_first-1,(mas+place_first));
            place_first--;
        }
        while (i<place_first){
            if (*(mas+i)>=*(mas+place_first)){
                swap_value_or((mas+i),(mas+place_first-1));
                swap_value_or((mas+place_first),(mas+place_first-1));
                place_first--;
                break;
            }
            i++;
        }
    }

}


void q_sort(int *mas, int len){
    if (len>3){                                     //Оптимальное значение тут 3
        int *main_i, *start = mas, *end = mas + len - 1;
        if (*mas >= *(mas + len - 1) && *mas <= *(mas + len/2) || *mas <= *(mas + len - 1) && *mas >= *(mas + len/2) ){
            main_i = mas;
        }
        else if (*(mas + len - 1) >= *mas && *(mas + len - 1) <= *(mas + len/2) || *(mas + len - 1) <= *mas && *(mas + len - 1) >= *(mas + len/2)){
            main_i = (mas + len -1);
        }
        else{
            main_i = (mas + len/2);
        }
        while(1) {
            while (*(start) <= *(main_i) && start <= mas + len - 1) {
                ++start;
                if (start > end) {
                    start--;
                    break;
                }
            }
            while (*(end) > *(main_i) && end >= mas) {
                --end;
            }
            if (start < end){
                swap_value_or(start, end);
                if(main_i == end){
                    main_i = start;
                }
                else if (main_i == start){
                    main_i = end;
                }
            }
            else {
                swap_value_or(end, main_i);
                main_i = end;
                break;
            }
        }
        int *main_help = main_i;
        int len_im = 0;
        for(; main_i >mas;main_i--, len_im++){ }
        q_sort(main_help + 1, len - len_im - 1);
        q_sort(mas, len_im);
    }
    else{
        selection_sort(mas,len,0);
    }
}


void in_2_copy_1(int *mas1,int * mas2, int len){
    for (int i = 0; i < len; ++i){
        *(mas2+i) = *(mas1+i);
    }
}


char is_sort(int *mas, int len, int if1down){
    if(!if1down){
        for(int i = 0; i<len-1; ++i){
            if (*(mas+i)>*(mas+i+1)){
                printf("Not up\n");
                return 0;
            }
        }
        printf("It up\n");
    }
    else{
        for(int i = 0; i<len-1; ++i){
            if (*(mas+i)<*(mas+i+1)){
                printf("Not down\n");
                return 0;
            }
        }
        printf("It down\n");
    }
}


char el_in_sort_mas(int *mas, size_t len_mas, int element){

    if ( len_mas < 4){
        for (int i = 0; i < len_mas; ++i){
            if (element == *(mas + i)){
                return 1;
            }
        }
        return 0;
    }
    if (element < *(mas + len_mas/2)){
        return el_in_sort_mas(mas, len_mas/2, element);
    }
    return el_in_sort_mas(mas + len_mas/2, len_mas - len_mas/2, element);
}


void matching_elements(int *masn, size_t len_masn,
                       int *mask, size_t len_mask,
                       int *mas_new, size_t len_mas_new){
    q_sort(masn, len_masn);
    int k = 0, new = 0;
    while(1){
        while (k<len_mask){
            if(el_in_sort_mas(masn, len_masn, *(mask + k))){
                *(mas_new + new) = *(mask + k);
                new++;
                if (new == len_mas_new){
                    return;
                }
            }
            k++;
        }
        return;
    }
}


int more_meet_el(int *mas, size_t len_mas){
    if (len_mas == 1)return *mas;
    int *help_mas = malloc(len_mas*sizeof(int));
    for (int i = 0; i < len_mas; ++i){
        help_mas[i] = mas[i];
    }
    q_sort(help_mas, len_mas);
    int kolv_el_max = 1, kolv_el_now = 1, ind_max_el = 0;
    for (int i = 1; i < len_mas; ++i){
        if (*(help_mas+i)==*(help_mas+i-1)){
            kolv_el_now++;
            ind_max_el = kolv_el_max>kolv_el_now?ind_max_el:i-1;
            kolv_el_max = kolv_el_max>kolv_el_now?kolv_el_max:kolv_el_now;
        }
        else{
            kolv_el_now =1;
        }
    }
    int g = *(help_mas + ind_max_el);
    free(help_mas);
    return g;
}


void insertion_sort(int *mas, int len_mas){
    for (int i = 1; i < len_mas; ++i) {
        for (int j = i; j>0;--j){
            if (*(mas + j) < *(mas + j - 1)){
                swap_value_or(mas+j, mas + j - 1);
            }
        }
    }
}

//2
void counting_sort(int *mas, size_t len_mas){
    int min_el = 0, max_el = 0;
    for (int i = 0; i < len_mas; ++i){
        if (*(mas + i) > max_el)max_el = *(mas + i);
        if (*(mas + i) < min_el)min_el = *(mas + i);
    }

    if (min_el >= 0) {
        int *help_plus = calloc(max_el+1, sizeof(int));
        if (help_plus == NULL){printf("error malloc");return;}
        for (int i = 0; i < len_mas; ++i) {
            *(help_plus + *(mas + i)) += 1;
        }
        int mas_now = 0;
        for (int i = 0; i <= max_el; ++i){
            for (int g = 0; g < *(help_plus + i); ++g) {
                *(mas + mas_now) = i;
                mas_now++;
            }
        }
        free(help_plus);
    }
    else{
        int *help_plus = calloc(max_el+1, sizeof(int));
        int *help_minus = calloc(-min_el+1, sizeof(int));
        if (help_plus == NULL){printf("error help_plus malloc");return;}
        if (help_minus == NULL){printf("error help_minus malloc");return;}
        for (int i = 0; i < len_mas; ++i) {
            if (*(mas + i) >= 0) {
                *(help_plus + *(mas + i)) += 1;
            }
            else{
                *(help_minus - *(mas + i)) += 1;
            }
        }
        int mas_now = 0;
        print_array(help_minus, -min_el+1);
        for (int i = -min_el; i >= 1; +--i){
            for (int g = 0; g < *(help_minus+i); ++g) {
                *(mas + mas_now) = -i;
                mas_now++;
                printf("mas_now = %d\n", mas_now);
            }
        }
        printf("mas_now = %d\n ", mas_now);
        for (int i = 1; i <= max_el; ++i){
            for (int g = 0; g < *(help_plus + i); ++g) {
                *(mas + mas_now) = i;
                mas_now++;
            }
        }
        free(help_plus);
        free(help_minus);
    }
}