#include "object.h"

void object_print(Object *object) {
    switch (object->type) {
        case INT: printf("%d", object->i); return;
        case FLOAT: printf("%f", object->f); return;
        case CHAR: printf("%c", object->c); return;
        case BOOL: printf("%s", object->b ? "true" : "false"); return;
    }
}

void object_sum(Object *object, const Object *other) {
    if (object->type == other->type) {
        switch (object->type){
            case INT: object->i += other->i; return;
            case FLOAT: object->f += other->f; return;
            case CHAR: object->c += other->c; return;
            case BOOL:
            if (object->b == other->b == false) {
                object->b = false;
                return;
            }
            object->b = true;
            return;
        }
    }
    if (object->type == INT && other->type == FLOAT) {
        object->type = FLOAT;
        object->f = (float)object->i + other->f;
        return;
    }
    if (object->type == FLOAT && other->type == INT) {
        object->f += (float)other->i;
        return;
    }
}

void object_neg(Object *object) {
    switch (object->type) {
        case INT: object->i = -object->i; return;
        case FLOAT: object->f = -object->f; return;
        case CHAR: return;
        case BOOL: object->b = object->b ? false : true; return;
}
