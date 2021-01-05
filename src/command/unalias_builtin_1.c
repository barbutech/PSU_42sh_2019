/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias_builtin.c
*/

#include "command/builtin.h"
#include "command/unalias_builtin.h"
#include "aliases/alias.h"
#include "util/entry.h"

unalias_builtin *unalias_builtin_construct(type *object_type)
{
    unalias_builtin *self = (unalias_builtin *) builtin_construct(object_type);

    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &unalias_builtin_finalize;
    return (self);
}

unalias_builtin *unalias_builtin_new(alias *alias)
{
    unalias_builtin *self = unalias_builtin_construct(TYPE_UNALIAS_BUILTIN);

    RETURN_VAL_IF_FAIL(self != NULL, NULL);
    self->map = map_new();
    self->alias = alias;
    self->arguments = NULL;

    ((builtin *) self)->is = &unalias_builtin_is;
    ((builtin *) self)->execute = &unalias_builtin_execute;
    ((builtin *) self)->prepare = &unalias_builtin_prepare;
    return (self);
}

type *unalias_builtin_get_type(void)
{
    return (type_register(
        "builtin.unalias_builtin",
        sizeof(unalias_builtin),
        TYPE_BUILTIN
    ));
}

void unalias_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    unalias_builtin *self = (unalias_builtin *) parent;

    object_unref((object *) self->map);
    object_unref((object *) self->arguments);
    builtin_finalize(parent);
}
