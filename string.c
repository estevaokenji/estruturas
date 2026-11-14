#include "string.h"
#include <string.h>
#include <stdint.h>

String string_new() {
    String string = {
        .data = NULL,
        .length = 0,
        .capacity = 0
    };
    if (string_reserve(&string, 8)) string.data[0] = '\0';
    return string;
}

void string_free(String *string) {
    free(string->data);
    string->data = NULL;
    string->length = 0;
    string->capacity = 0;
}

bool string_reserve(String *string, size_t required) {
    if (required <= string->capacity) return true;
    size_t capacity = string->capacity ? string->capacity : 8;
    while (capacity < required) {
        if (capacity > SIZE_MAX / 2) {
            capacity = required;
            break;
        }
        capacity *= 2;
    }
    char *temp = realloc(string->data, capacity);
    if (temp == NULL) return false;
    string->data = temp;
    string->capacity = capacity;
    return true;
}

bool string_concatenate(String *string, const String *other) {
    if (other->length > SIZE_MAX - string->length - 1) return false;
    size_t length = string->length;
    size_t other_length = other->length;
    if (!string_reserve(string, length + other_length + 1)) return false;
    memmove(string->data + length, other->data, other_length + 1);
    string->length = length + other_length;
    return true;
}

bool string_append(String *string, char character) {
    if (string->length > SIZE_MAX - 2) return false;
    if (!string_reserve(string, string->length+2)) return false;
    string->data[string->length++] = character;
    string->data[string->length] = '\0';
    return true;
}

char string_get(const String *string, size_t idx) {
    if (idx >= string->length) return '\0';
    return string->data[idx];
}

String string_slice(const String *string, size_t start, size_t end) {
    String slice = {
        .data = NULL,
        .length = 0,
        .capacity = 0
    };
    if (start > end || end > string->length)
        return slice;
    size_t length = end - start;
    if (!string_reserve(&slice, length + 1))
        return slice;
    memcpy(slice.data, string->data + start, length);
    slice.data[length] = '\0';
    slice.length = length;
    return slice;
}

int string_compare(const String *string, const String *other) {
    return strcmp(string->data, other->data);
}

int string_find(const String *string, const String *substring) {
    if (string->length == 0 || substring->length == 0) return -1;
    char *result = strstr(string->data, substring->data);
    if (result == NULL) return -1;
    return (int)(result-string->data);
}

bool string_replace(String *string, const String *old, const String *new) {
    if (!string || !old || !new || !string->data || !old->data || !new->data) return false;
    if (old->length == 0) return false;
    int idx = string_find(string, old);
    if (idx == -1) return false;
    size_t start = (size_t)idx;
    size_t suffix_start = start + old->length;
    size_t suffix_length = string->length - suffix_start;
    if (new->length > SIZE_MAX - start) return false;
    size_t length = start + new->length;
    if (suffix_length > SIZE_MAX - length - 1) return false;
    length += suffix_length;
    String result = {
        .data = NULL,
        .length = 0,
        .capacity = 0
    };
    if (!string_reserve(&result, length + 1)) return false;
    memcpy(result.data, string->data, start);
    memcpy(result.data + start, new->data, new->length);
    memcpy(result.data + start + new->length, string->data + suffix_start, suffix_length);
    result.length = length;
    result.data[length] = '\0';
    string_free(string);
    *string = result;
    return true;
}