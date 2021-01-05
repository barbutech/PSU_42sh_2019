/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The string_format class.
*/

#include <stdarg.h>
#include "format/string_format.h"
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

string_format *string_format_construct(type *object_type)
{
    string_format *self = (string_format *) format_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &string_format_finalize;

    return (self);
}

string_format *string_format_new(void)
{
    string_format *self = string_format_construct(TYPE_STRING_FORMAT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((format *) self)->process = &string_format_process;
    ((format *) self)->get_flag = &string_format_get_flag;

    return (self);
}

type *string_format_get_type(void)
{
    return (type_register(
        "format.string_format",
        sizeof(string_format),
        TYPE_FORMAT
    ));
}

void string_format_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    format_finalize(parent);
}
