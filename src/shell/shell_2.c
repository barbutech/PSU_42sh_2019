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

void shell_init(shell *self, char **env)
{
    RETURN_IF_FAIL(self != NULL);

    environment_defaults(self->environment, env);

    SHELL_INIT;
}

void shell_start(shell *self)
{
    RETURN_IF_FAIL(self != NULL);

    self->running = TRUE;
}

void shell_stop(shell *self)
{
    RETURN_IF_FAIL(self != NULL);

    self->running = FALSE;
}

bool is_executed_internally(FILE *stream)
{
    if (stream != stdin)
        return (TRUE);

    return (!isatty(0));
}

void shell_exit(shell *self)
{
    RETURN_IF_FAIL(self != NULL);

    if (!is_executed_internally(self->stream))
        console_writeln("exit");
}
