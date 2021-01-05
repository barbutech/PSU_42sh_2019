/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The string class header.
*/

#ifndef STRING_H
#define STRING_H

#include "lang/object.h"
#include "type.h"
#include "base.h"

typedef struct string string;
typedef struct object object;

struct object;

struct string {
    object parent;
    char *value;
    int length;
};

#define TYPE_STRING (string_get_type())

#define STRING_SPLIT \
int occurences = string_count_occurences(self, separator); \
string **array = malloc(sizeof(string *) * (occurences + 2)); \
string *str = string_clone(self); \
int index_of = string_index_of(str, separator); \
int i = 0; \
for (; index_of != -1; i++) { \
    array[i] = string_substring(str, 0, index_of); \
    if (array[i]->length == 0) { \
        object_unref((object *) array[i]); \
        i--; \
    } \
    string *tmp = string_substring(str, \
        index_of + separator->length, str->length); \
    object_unref((object *) str); \
    str = tmp; \
    index_of = string_index_of(str, separator); \
} \
array[i++] = str; \
if (str->length == 0) { \
    object_unref((object *) str); \
    i--; \
} \
array[i] = NULL;

string *string_construct(type *object_type);
string *string_new(char *value);
string *string_new_with_length(char *value, int length);
string *string_new_with_range(char *value, int start, int end);
string *string_new_from_int(int n);
string *string_substring(string *self, int start, int end);
int string_index_of(string *self, string *needle);
int string_count_occurences(string *self, string *needle);
string **string_split(string *self, string *separator);
string *string_add(string *self, string *another);
bool string_has_prefix(string *self, string *another);
string *string_stringify(object *parent);
bool string_equals(object *parent, object *another);
char *string_clone_to_primitive(string *self);
string *string_clone(string *self);
type *string_get_type(void);
void string_finalize(object *parent);

#endif
