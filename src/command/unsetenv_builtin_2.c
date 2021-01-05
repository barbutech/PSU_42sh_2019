/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The unsetenv_builtin class.
*/

#include "command/unsetenv_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "util/node.h"
#include "env/environment.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

bool unsetenv_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    unsetenv_builtin *self = (unsetenv_builtin *) parent;

    if (arguments->size < 1) {
        console_errln("unsetenv: Too few arguments.");
        return (FALSE);
    }

    object_unref((object *) self->arguments);
    object_ref((object *) arguments);
    self->arguments = arguments;

    return (TRUE);
}

bool unsetenv_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    unsetenv_builtin *self = (unsetenv_builtin *) parent;

    node *tmp = self->arguments->head;

    while (tmp != NULL) {
        environment_remove(self->environment, (string *) tmp->value);
        tmp = tmp->next;
    }

    return (TRUE);
}

bool unsetenv_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("unsetenv");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
