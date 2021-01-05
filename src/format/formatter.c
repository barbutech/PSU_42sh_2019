/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The formatter class.
*/

#include <stdio.h>
#include <stdarg.h>
#include "format/formatter.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/array.h"
#include "format/format.h"
#include "format/string_format.h"
#include "format/chararray_format.h"
#include "format/int_format.h"
#include "type.h"
#include "base.h"

formatter *formatter_construct(type *object_type)
{
    formatter *self = (formatter *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &formatter_finalize;

    return (self);
}

formatter *formatter_new(void)
{
    formatter *self = formatter_construct(TYPE_FORMATTER);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->formats = array_new(3);

    format *string_fmt = (format *) string_format_new();
    format *chararray_fmt = (format *) chararray_format_new();
    format *int_fmt = (format *) int_format_new();

    array_set(self->formats, (object *) string_fmt, 0);
    array_set(self->formats, (object *) chararray_fmt, 1);
    array_set(self->formats, (object *) int_fmt, 2);

    object_unref((object *) string_fmt);
    object_unref((object *) chararray_fmt);
    object_unref((object *) int_fmt);

    return (self);
}

string *formatter_format(formatter *self, char *fmt, va_list args)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *str_format = string_new(fmt);
    string *flag = string_new("%");
    string *result = string_new("");
    int index_of;

    FORMATTER_FORMAT;

    string *tmp = string_add(result, str_format);
    object_unref((object *) result);
    result = tmp;
    object_unref((object *) str_format);
    object_unref((object *) flag);

    return (result);
}

type *formatter_get_type(void)
{
    return (type_register(
        "format.formatter",
        sizeof(formatter),
        TYPE_OBJECT
    ));
}

void formatter_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    formatter *self = (formatter *) parent;

    object_unref((object *) self->formats);

    object_finalize(parent);
}
