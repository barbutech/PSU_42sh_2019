/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The command_manager class.
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "command/command_manager.h"
#include "command/builtin.h"
#include "argument/argument.h"
#include "lang/object.h"
#include "lang/string.h"
#include "regex/regex.h"
#include "shell/shell.h"
#include "util/list.h"
#include "util/node.h"
#include "io/console.h"
#include "io/path.h"
#include "io/file.h"
#include "try.h"
#include "type.h"
#include "base.h"
#include "errno.h"

void command_manager_register(command_manager *self, builtin *builtin_)
{
    RETURN_IF_FAIL(self != NULL);

    list_push(self->builtins, (object *) builtin_);
}

static bool is_regex(string *str)
{
    for (int i = 0; i < str->length; i++) {
        if (str->value[i] == '(')
            return (TRUE);

        if (str->value[i] == '*')
            return (TRUE);
    }

    return (FALSE);
}

bool command_manager_call(
    command_manager *self, string *name, list *arguments, redirection redirect)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    self->shell->last_return_value = 0;

    list *args = list_new();
    node *tmp = arguments->head;
    string *str_path = environment_get_pwd(self->shell->environment);
    path *path_ = path_new_from_absolute(str_path);
    CMD_MANAGER_CALL;
    self->shell->last_return_value = 1;
    return (FALSE);
}
