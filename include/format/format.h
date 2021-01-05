/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The format abstract class header.
*/

#ifndef FORMAT_H
#define FORMAT_H

#include <stdarg.h>
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct format format;

struct format {
    object parent;
    string *(*process)(format *self, va_list list);
    char (*get_flag)(format *self);
};

#define TYPE_FORMAT (format_get_type())

format *format_construct(type *object_type);
string *format_process(format *self, va_list args);
char format_get_flag(format *self);
type *format_get_type(void);
void format_finalize(object *parent);


#endif
