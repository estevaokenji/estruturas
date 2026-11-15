#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <stdbool.h>

#define INT 1
#define FLOAT 2
#define CHAR 3
#define BOOL 4

typedef struct {
    union {
        int i;
        float f;
        char c;
        bool b;
    };
    int type;
} Object;

void object_print(Object *object);
void object_sum(Object *object, const Object *other);
void object_neg(Object *object);

#endif