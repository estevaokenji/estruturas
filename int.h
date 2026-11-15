#ifndef INT_H
#define INT_H

#include <stdint.h>

typedef struct {
    int signal;
    uint8_t *digits;
    size_t size;
} Int;

Int int_new(const char text[]);
void int_free(Int *num);
Int int_sum(Int a, Int b);
void int_print(Int num);

#endif