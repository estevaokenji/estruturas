#include "int.h"

Int int_new(const char text[]) {
    Int num;
    int inicio = 0;
    if (text[0] == '-') {
        num.signal = -1;
        inicio = 1;
    } else if (text[0] == '+') {
        num.signal = 1;
        inicio = 1;
    } else {
        num.signal = 1;
    }
    num.size = strlen(text) - inicio;
    num.digits = (uint8_t*)malloc(num.size * sizeof(uint8_t));
    for (size_t i = 0; i < num.size; i++) {
        num.digits[i] = text[strlen(text) - 1 - i] - '0';
    }
    return num;
}

void int_free(Int *num) {
    free(num->digits);
    num->digits = NULL;
    num->size = 0;
}

Int int_sum(Int *a, Int *b) {
    Int res;
    res.signal = 1;
    size_t max_tam = (a->size > b->size) ? a->size : b->size;
    res.digits = (uint8_t *)calloc(max_tam + 1, sizeof(uint8_t));
    int carry = 0;
    size_t i = 0;
    while (i < max_tam || carry > 0) {
        int soma = carry;
        if (i < a->size) soma += a->digits[i];
        if (i < b->size) soma += b->digits[i];
        res.digits[i] = soma % 10;
        carry = soma / 10;
        i++;
    }
    res.size = i;
    return res;
}

void int_print(Int num) {
    if (num.signal == -1) printf("-");
    for (size_t i = num.size; i > 0; i--) {
        printf("%d", num.digits[i - 1]);
    }
}