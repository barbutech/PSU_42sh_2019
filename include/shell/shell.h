/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The shell class header.
*/

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include "lang/object.h"
#include "command/command_manager.h"
#include "var/variable_manager.h"
#include "env/environment.h"
#include "aliases/alias.h"
#include "type.h"
#include "base.h"

typedef struct shell shell;
typedef struct command_manager command_manager;

struct command_manager;

struct shell {
    object parent;
    FILE *stream;
    command_manager *cmd_manager;
    variable_manager *var_manager;
    environment *environment;
    alias *alias;
    bool running;
    int last_return_value;
};

#define TYPE_SHELL (shell_get_type())

#define SHELL_INIT \
builtin *cd_btin = (builtin *) cd_builtin_new(self->environment); \
command_manager_register(self->cmd_manager, cd_btin); \
builtin *env_btin = (builtin *) env_builtin_new(self->environment); \
command_manager_register(self->cmd_manager, env_btin); \
builtin *exit_btin = (builtin *) exit_builtin_new(self); \
command_manager_register(self->cmd_manager, exit_btin); \
builtin *setenv_btin = (builtin *) setenv_builtin_new(self->environment); \
command_manager_register(self->cmd_manager, setenv_btin); \
builtin *unsetenv_btin = \
    (builtin *) unsetenv_builtin_new(self->environment); \
command_manager_register(self->cmd_manager, unsetenv_btin); \
builtin *echo_btin = (builtin *) echo_builtin_new(); \
command_manager_register(self->cmd_manager, echo_btin); \
builtin *alias_btin = (builtin *) alias_builtin_new(self->alias); \
command_manager_register(self->cmd_manager, alias_btin); \
builtin *unalias_btin = (builtin *) unalias_builtin_new(self->alias); \
command_manager_register(self->cmd_manager, unalias_btin); \
builtin *setvar_btin = (builtin *) setvar_builtin_new(self->var_manager); \
command_manager_register(self->cmd_manager, setvar_btin); \
builtin *repeat_btin = (builtin *) repeat_builtin_new(self->cmd_manager); \
command_manager_register(self->cmd_manager, repeat_btin); \
builtin *which_btin = (builtin *) which_builtin_new( \
    self->cmd_manager, self->environment, self->alias); \
command_manager_register(self->cmd_manager, which_btin); \
builtin *where_btin = (builtin *) where_builtin_new( \
    self->cmd_manager, self->environment, self->alias); \
command_manager_register(self->cmd_manager, where_btin); \
object_unref((object *) cd_btin); \
object_unref((object *) env_btin); \
object_unref((object *) exit_btin); \
object_unref((object *) setenv_btin); \
object_unref((object *) unsetenv_btin); \
object_unref((object *) echo_btin); \
object_unref((object *) alias_btin); \
object_unref((object *) unalias_btin); \
object_unref((object *) setvar_btin); \
object_unref((object *) repeat_btin); \
object_unref((object *) which_btin); \
object_unref((object *) where_btin);

#define ALIAS_CMP_LINE \
while (tmp) { \
    int count = 0; \
    entry *entry_ = (entry *) tmp->value; \
    string *key = (string *) entry_->key; \
    for (; is_alphanum(line->value[count]); count++); \
    string *to_check = string_substring(line, 0, count); \
    if (string_equals((object *) key, (object *) to_check)) { \
        string *tmp2 = alias_replace(self->alias, line, key); \
        object_unref((object *) line); \
        object_ref((object *) tmp2); \
        line = tmp2; \
        object_unref((object *) to_check); \
        object_unref((object *) tmp2); \
        return (line); \
    } \
    tmp = tmp->next; \
    object_unref((object *) to_check); \
}

#define SHELL_LOOP \
while (self->running) { \
    show_prompt(self); \
    string *line = get_next_line(self->stream); \
    if (line == NULL) \
        break; \
    self->last_return_value = 0; \
    line = alias_compare_line(self, line); \
    lexer *lexer_ = lexer_new(line); \
    lexer_lexe(lexer_); \
    parser *parser_ = parser_new(lexer_, self->cmd_manager, \
        self->var_manager); \
    parser_parse(parser_); \
    interpreter *interpreter_ = interpreter_new(parser_, self->cmd_manager, \
        self->var_manager); \
    interpreter_interprete(interpreter_); \
    object_unref((object *) var_return_value); \
    var_return_value = string_new_from_int(self->last_return_value); \
    variable_manager_set(self->var_manager, \
        var_return_name, var_return_value); \
    object_unref((object *) lexer_); \
    object_unref((object *) parser_); \
    object_unref((object *) interpreter_); \
    object_unref((object *) line); \
}

shell *shell_construct(type *object_type);
shell *shell_new(FILE *stream);
void shell_init(shell *self, char **env);
void shell_start(shell *self);
void shell_stop(shell *self);
bool is_executed_internally(FILE *stream);
void shell_exit(shell *self);
void shell_loop(shell *self);
type *shell_get_type(void);
void shell_finalize(object *parent);

#endif
