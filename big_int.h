typedef struct big_int{
    unsigned char* number;
    unsigned int length;
} big_int;

big_int* big_int_get(char *bin_number);

void big_int_print(big_int *number);

void big_int_dlz(big_int *n);

char big_int_equal(big_int *n1, big_int *n2);

void big_int_free(big_int *n);

void big_int_swap(big_int *n1, big_int *n2);