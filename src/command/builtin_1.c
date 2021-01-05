/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The builtin abstract class.
*/

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

builtin *builtin_construct(type *object_type)
{
    builtin *self = (builtin *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->prepare = NULL;
    self->execute = NULL;
    self->dispose = NULL;
    self->is = NULL;

    ((object *) self)->finalize = &builtin_finalize;

    return (self);
}

type *builtin_get_type(void)
{
    return (type_register(
        "builtin.builtin",
        sizeof(builtin),
        TYPE_OBJECT
    ));
}

void builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    object_finalize(parent);
}
