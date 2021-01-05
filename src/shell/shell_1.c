/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The shell class.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell/shell.h"
#include "lang/object.h"
#include "lang/string.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"
#include "aliases/alias.h"
#include "command/alias_builtin.h"
#include "command/unalias_builtin.h"
#include "command/command_manager.h"
#include "command/builtin.h"
#include "command/cd_builtin.h"
#include "command/set_var_builtin.h"
#include "command/echo_builtin.h"
#include "command/env_builtin.h"
#include "command/exit_builtin.h"
#include "command/setenv_builtin.h"
#include "command/unsetenv_builtin.h"
#include "command/repeat_builtin.h"
#include "command/which_builtin.h"
#include "command/where_builtin.h"
#include "var/variable_manager.h"
#include "env/environment.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

shell *shell_construct(type *object_type)
{
    shell *self = (shell *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &shell_finalize;

    return (self);
}

shell *shell_new(FILE *stream)
{
    shell *self = shell_construct(TYPE_SHELL);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->stream = stream;

    self->environment = environment_new();
    self->cmd_manager = command_manager_new(self);
    self->var_manager = variable_manager_new(self->environment);
    self->alias = alias_new();

    self->running = FALSE;
    self->last_return_value = 0;

    return (self);
}

type *shell_get_type(void)
{
    return (type_register(
        "shell.shell",
        sizeof(shell),
        TYPE_OBJECT
    ));
}

void shell_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    shell *self = (shell *) parent;

    object_unref((object *) self->environment);
    object_unref((object *) self->cmd_manager);
    object_unref((object *) self->var_manager);
    object_unref((object *) self->alias);

    object_finalize(parent);
}
