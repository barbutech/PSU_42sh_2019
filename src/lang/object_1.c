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

object *object_construct(type *object_type)
{
    object *self = (object *) type_instantiate(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->ref_count = 1;
    self->object_type = object_type;

    self->finalize = &object_finalize;
    self->equals = NULL;

    return (self);
}

type *object_get_type(void)
{
    return (type_register(
        "lang.object",
        sizeof(object),
        NULL
    ));
}

void object_finalize(object *self)
{
    RETURN_IF_FAIL(self != NULL);

    type_free(self->object_type);
    free(self);
}
