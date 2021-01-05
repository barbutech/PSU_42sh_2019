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

command_manager *command_manager_construct(type *object_type)
{
    command_manager *self = (command_manager *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &command_manager_finalize;

    return (self);
}

command_manager *command_manager_new(shell *shell)
{
    command_manager *self = command_manager_construct(TYPE_COMMAND_MANAGER);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->builtins = list_new();
    self->shell = shell;

    self->fd_in = 0;

    return (self);
}

type *command_manager_get_type(void)
{
    return (type_register(
        "command.command_manager",
        sizeof(command_manager),
        TYPE_OBJECT
    ));
}

void command_manager_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    command_manager *self = (command_manager *) parent;

    object_unref((object *) self->builtins);

    object_finalize(parent);
}
