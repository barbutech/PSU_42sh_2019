/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The chararray_format class.
*/

#include <stdarg.h>
#include "format/chararray_format.h"
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

chararray_format *chararray_format_construct(type *object_type)
{
    chararray_format *self = (chararray_format *) format_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &chararray_format_finalize;

    return (self);
}

chararray_format *chararray_format_new(void)
{
    chararray_format *self = chararray_format_construct(TYPE_CHARARRAY_FORMAT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((format *) self)->process = &chararray_format_process;
    ((format *) self)->get_flag = &chararray_format_get_flag;

    return (self);
}

type *chararray_format_get_type(void)
{
    return (type_register(
        "format.chararray_format",
        sizeof(chararray_format),
        TYPE_FORMAT
    ));
}

void chararray_format_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    format_finalize(parent);
}
