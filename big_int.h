typedef struct big_int{
    unsigned char* number;
    unsigned int length;
} big_int;

big_int* big_int_get(char *bin_number);

void big_int_print(big_int *number);