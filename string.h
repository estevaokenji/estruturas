#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} String;

String string_new();
void string_free(String *string);

bool string_append(String *string, char character);
bool string_concatenate(String *string, const String *other);

char string_get(const String *string, size_t idx);
String string_slice(const String *string, size_t start, size_t end);

int string_compare(const String *string, const String *other);
int string_find(const String *string, const String *substring);
bool string_replace(String *string, const String *old, const String *new);

#endif