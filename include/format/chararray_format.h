/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The chararray_format class header.
*/

#ifndef CHARARRAY_FORMAT_H
#define CHARARRAY_FORMAT_H

#include <stdarg.h>
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct chararray_format chararray_format;

struct chararray_format {
    format parent;
};

#define TYPE_CHARARRAY_FORMAT (chararray_format_get_type())

chararray_format *chararray_format_construct(type *object_type);
chararray_format *chararray_format_new(void);
string *chararray_format_process(format *parent, va_list args);
char chararray_format_get_flag(format *parent);
type *chararray_format_get_type(void);
void chararray_format_finalize(object *parent);

#endif
