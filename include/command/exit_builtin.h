/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The exit_builtin class header.
*/

#ifndef EXIT_BUILTIN_H
#define EXIT_BUILTIN_H

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "shell/shell.h"
#include "type.h"
#include "base.h"

typedef struct exit_builtin exit_builtin;

struct exit_builtin {
    builtin parent;
    shell *shell;
};

#define TYPE_EXIT_BUILTIN (exit_builtin_get_type())

exit_builtin *exit_builtin_construct(type *object_type);
exit_builtin *exit_builtin_new(shell *shell_);
bool exit_builtin_execute(builtin *parent);
bool exit_builtin_is(builtin *parent, string *name);
type *exit_builtin_get_type(void);
void exit_builtin_finalize(object *parent);

#endif
