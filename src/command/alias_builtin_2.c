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

bool alias_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    alias_builtin *self = (alias_builtin *) parent;

    object_unref((object *)self->arguments);
    self->arguments = arguments;
    object_ref((object *) self->arguments);

    return (TRUE);
}

bool alias_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    alias_builtin *self = (alias_builtin *) parent;

    if ((self->arguments->size % 2) != 0)
        return (FALSE);

    ALIAS_BUILTIN_EXEC;
    return (TRUE);
}

bool alias_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("alias");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
