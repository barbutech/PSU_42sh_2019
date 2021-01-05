/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** unalias_builtin.c
*/

#include "command/builtin.h"
#include "command/alias_builtin.h"
#include "aliases/alias.h"
#include "util/entry.h"

alias_builtin *alias_builtin_construct(type *object_type)
{
    alias_builtin *self = (alias_builtin *) builtin_construct(object_type);

    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &alias_builtin_finalize;
    return (self);
}

alias_builtin *alias_builtin_new(alias *alias)
{
    alias_builtin *self = alias_builtin_construct(TYPE_ALIAS_BUILTIN);

    RETURN_VAL_IF_FAIL(self != NULL, NULL);
    self->map = map_new();
    self->alias = alias;
    self->arguments = NULL;

    ((builtin *) self)->is = &alias_builtin_is;
    ((builtin *) self)->execute = &alias_builtin_execute;
    ((builtin *) self)->prepare = &alias_builtin_prepare;
    return (self);
}

type *alias_builtin_get_type(void)
{
    return (type_register(
        "builtin.alias_builtin",
        sizeof(alias_builtin),
        TYPE_BUILTIN
    ));
}

void alias_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    alias_builtin *self = (alias_builtin *) parent;

    object_unref((object *) self->map);
    object_unref((object *) self->arguments);
    builtin_finalize(parent);
}
