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

exit_builtin *exit_builtin_construct(type *object_type)
{
    exit_builtin *self = (exit_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &exit_builtin_finalize;

    return (self);
}

exit_builtin *exit_builtin_new(shell *shell_)
{
    exit_builtin *self = exit_builtin_construct(TYPE_EXIT_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->shell = shell_;

    ((builtin *) self)->execute = &exit_builtin_execute;
    ((builtin *) self)->is = &exit_builtin_is;

    return (self);
}

type *exit_builtin_get_type(void)
{
    return (type_register(
        "builtin.exit_builtin",
        sizeof(exit_builtin),
        TYPE_BUILTIN
    ));
}

void exit_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    builtin_finalize(parent);
}
