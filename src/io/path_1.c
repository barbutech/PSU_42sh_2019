/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The path class.
*/

#include <stdlib.h>
#include "io/path.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/stack.h"
#include "type.h"
#include "base.h"

path *path_construct(type *object_type)
{
    path *self = (path *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &path_finalize;

    return (self);
}

type *path_get_type(void)
{
    return (type_register(
        "io.path",
        sizeof(path),
        TYPE_OBJECT
    ));
}

void path_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    path *self = (path *) parent;

    object_unref((object *) self->value);

    object_finalize(parent);
}
