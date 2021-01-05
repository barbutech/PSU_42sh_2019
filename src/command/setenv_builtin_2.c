/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The setenv_builtin class.
*/

#include "command/setenv_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

bool setenv_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    setenv_builtin *self = (setenv_builtin *) parent;

    if (arguments->size < 1) {
        console_errln("setenv: Too few arguments.");
        return (FALSE);
    }
    if (arguments->size > 2) {
        console_errln("setenv: Too many arguments.");
        return (FALSE);
    }
    object_unref((object *) self->key);
    object_unref((object *) self->value);
    SETENV_BUILTIN_PREPARE;
    return (TRUE);
}

bool setenv_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    setenv_builtin *self = (setenv_builtin *) parent;

    environment_set(self->environment, self->key, self->value, TRUE);
    return (TRUE);
}

bool setenv_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("setenv");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
