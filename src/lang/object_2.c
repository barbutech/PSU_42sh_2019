/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The object abstract class.
*/

#include <stdlib.h>
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

void object_ref(object *self)
{
    RETURN_IF_FAIL(self != NULL);

    self->ref_count++;
}

void object_unref(object *self)
{
    RETURN_IF_FAIL(self != NULL);

    self->ref_count--;

    if (self->ref_count != 0)
        return;

    self->finalize(self);
}

string *object_stringify(object *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (self->stringify == NULL)
        return (string_new(""));

    return (self->stringify(self));
}

bool object_equals(object *self, object *another)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (self->equals == NULL)
        return (FALSE);

    return (self->equals(self, another));
}
