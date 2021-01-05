/*
** EPITECH PROJECT, 2019
** test
** File description:
** set_var_builtin.c
*/

#include "io/console.h"
#include "base.h"
#include "type.h"
#include "command/set_var_builtin.h"
#include "var/variable_manager.h"

bool setvar_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    setvar_builtin *self = (setvar_builtin *) parent;

    SETVAR_BUILTIN_PREPARE;
    return (TRUE);
}

bool setvar_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    setvar_builtin *self = (setvar_builtin *) parent;

    variable_manager_set(self->variable_manager, self->key, self->value);
    return (TRUE);
}

bool setvar_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("set");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
