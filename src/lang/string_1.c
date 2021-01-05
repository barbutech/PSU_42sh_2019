/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The string class.
*/

#include <stdlib.h>
#include "lang/string.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

string *string_construct(type *object_type)
{
    string *self = (string *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &string_finalize;
    ((object *) self)->stringify = &string_stringify;
    ((object *) self)->equals = &string_equals;

    return (self);
}

string *string_clone(string *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    return (string_new_with_range(self->value, 0, self->length));
}

type *string_get_type(void)
{
    return (type_register(
        "lang.string",
        sizeof(string),
        TYPE_OBJECT
    ));
}

void string_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    string *self = (string *) parent;

    free(self->value);

    object_finalize(parent);
}
