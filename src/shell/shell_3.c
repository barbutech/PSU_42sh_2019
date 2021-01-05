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

static string *get_next_line(FILE *stream)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t nread;

    if ((nread = getline(&buffer, &len, stream)) == -1) {
        free(buffer);
        return (NULL);
    }
    string *line = string_new_with_length(buffer, nread);
    free(buffer);
    return (line);
}

static void show_prompt(shell *self)
{
    if (is_executed_internally(self->stream))
        return;
    string *user = environment_get_user(self->environment);
    string *pwd = environment_get_pwd(self->environment);
    string *home = environment_get_home(self->environment);
    if (home != NULL && string_has_prefix(pwd, home)) {
        string *tmp = string_substring(pwd, home->length, pwd->length);
        string *tilde = string_new("~");
        object_unref((object *) pwd);
        pwd = string_add(tilde, tmp);
        object_unref((object *) tmp);
        object_unref((object *) tilde);
    }
    console_write(
        "\e[1m\e[34m%S\e[0m \e[1m\e[32m%S\n%s $\e[0m ",
        user, pwd, self->last_return_value == 0 ? "\e[0m" : "\e[91m"
    );
    object_unref((object *) user);
    object_unref((object *) pwd);
    object_unref((object *) home);
}

string *alias_compare_line(shell *shell_first, string *line)
{
    shell *self = shell_first;
    node *tmp = self->alias->map->list->head;
    ALIAS_CMP_LINE;
    return (line);
}

void shell_loop(shell *self)
{
    RETURN_IF_FAIL(self != NULL);

    string *var_return_name = string_new("?");
    string *var_return_value = string_new_from_int(0);
    variable_manager_set(self->var_manager, var_return_name, var_return_value);
    SHELL_LOOP;
    object_unref((object *) var_return_value);
    object_unref((object *) var_return_name);
}
