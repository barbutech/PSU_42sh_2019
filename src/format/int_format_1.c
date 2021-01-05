/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The int_format class.
*/

#include <stdarg.h>
#include "format/int_format.h"
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

int_format *int_format_construct(type *object_type)
{
    int_format *self = (int_format *) format_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &int_format_finalize;

    return (self);
}

int_format *int_format_new(void)
{
    int_format *self = int_format_construct(TYPE_INT_FORMAT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((format *) self)->process = &int_format_process;
    ((format *) self)->get_flag = &int_format_get_flag;

    return (self);
}

type *int_format_get_type(void)
{
    return (type_register(
        "format.int_format",
        sizeof(int_format),
        TYPE_FORMAT
    ));
}

void int_format_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    format_finalize(parent);
}
