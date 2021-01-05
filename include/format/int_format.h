/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The int_format class header.
*/

#ifndef INT_FORMAT_H
#define INT_FORMAT_H

#include <stdarg.h>
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct int_format int_format;

struct int_format {
    format parent;
};

#define TYPE_INT_FORMAT (int_format_get_type())

int_format *int_format_construct(type *object_type);
int_format *int_format_new(void);
string *int_format_process(format *parent, va_list args);
char int_format_get_flag(format *parent);
type *int_format_get_type(void);
void int_format_finalize(object *parent);

#endif
