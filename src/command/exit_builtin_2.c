/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The exit_builtin class.
*/

#include "command/exit_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "shell/shell.h"
#include "type.h"
#include "base.h"

bool exit_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    exit_builtin *self = (exit_builtin *) parent;

    shell_stop(self->shell);
    return (TRUE);
}

bool exit_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("exit");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
