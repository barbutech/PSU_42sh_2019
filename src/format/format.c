/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The format class.
*/

#include <stdarg.h>
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

format *format_construct(type *object_type)
{
    format *self = (format *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->process = NULL;
    self->get_flag = NULL;

    ((object *) self)->finalize = &format_finalize;

    return (self);
}

string *format_process(format *self, va_list args)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (self->process == NULL)
        return (NULL);

    return (self->process(self, args));
}

char format_get_flag(format *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, '\0');

    if (self->get_flag == NULL)
        return ('\0');

    return (self->get_flag(self));
}

type *format_get_type(void)
{
    return (type_register(
        "format.format",
        sizeof(format),
        TYPE_OBJECT
    ));
}

void format_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    object_finalize(parent);
}
