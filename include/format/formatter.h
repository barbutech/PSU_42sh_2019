/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The formatter class header.
*/

#ifndef FORMATTER_H
#define FORMATTER_H

#include <stdio.h>
#include <stdarg.h>
#include "lang/object.h"
#include "lang/string.h"
#include "util/array.h"
#include "type.h"
#include "base.h"

typedef struct formatter formatter;

struct formatter {
    object parent;
    array *formats;
};

#define TYPE_FORMATTER (formatter_get_type())

#define FORMATTER_FORMAT \
while ((index_of = string_index_of(str_format, flag)) != -1) { \
    string *before = string_substring(str_format, 0, index_of); \
    string *tmp = string_add(result, before); \
    object_unref((object *) result); \
    result = tmp; \
    char flag_ = str_format->value[index_of + 1]; \
    for (int i = 0; i < self->formats->size; i++) { \
        format *format_ = (format *) array_get(self->formats, i); \
        if (format_ == NULL || flag_ != format_get_flag(format_)) { \
            object_unref((object *) format_); \
            continue; \
        } \
        string *result_process = format_process(format_, args); \
        string *tmp = string_add(result, result_process); \
        object_unref((object *) result); \
        result = tmp; \
        object_unref((object *) result_process); \
        object_unref((object *) format_); \
        break; \
    } \
    string *after = string_substring( \
        str_format, index_of + 2, str_format->length); \
    object_unref((object *) str_format); \
    str_format = after; \
    object_unref((object *) before); \
}

formatter *formatter_construct(type *object_type);
formatter *formatter_new(void);
string *formatter_format(formatter *self, char *fmt, va_list args);
type *formatter_get_type(void);
void formatter_finalize(object *parent);

#endif
