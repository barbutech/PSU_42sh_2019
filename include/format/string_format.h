/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The string_format class header.
*/

#ifndef STRING_FORMAT_H
#define STRING_FORMAT_H

#include <stdarg.h>
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct string_format string_format;

struct string_format {
    format parent;
};

#define TYPE_STRING_FORMAT (string_format_get_type())

string_format *string_format_construct(type *object_type);
string_format *string_format_new(void);
string *string_format_process(format *parent, va_list args);
char string_format_get_flag(format *parent);
type *string_format_get_type(void);
void string_format_finalize(object *parent);

#endif
