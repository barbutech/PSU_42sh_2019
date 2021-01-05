/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The which_builtin class.
*/

#include <stdlib.h>
#include "command/which_builtin.h"
#include "command/builtin.h"
#include "command/command_manager.h"
#include "env/environment.h"
#include "aliases/alias.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "util/node.h"
#include "io/file.h"
#include "io/path.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

which_builtin *which_builtin_construct(type *object_type)
{
    which_builtin *self = (which_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &which_builtin_finalize;

    return (self);
}

which_builtin *which_builtin_new(command_manager *cmd_manager,
    environment *env, alias *alias)
{
    which_builtin *self = which_builtin_construct(TYPE_WHICH_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->cmd_manager = cmd_manager;
    self->env = env;
    self->alias = alias;

    self->args = NULL;

    ((builtin *) self)->is = &which_builtin_is;
    ((builtin *) self)->execute = &which_builtin_execute;
    ((builtin *) self)->prepare = &which_builtin_prepare;

    return (self);
}

type *which_builtin_get_type(void)
{
    return (type_register(
        "command.which_builtin",
        sizeof(which_builtin),
        TYPE_BUILTIN
    ));
}

void which_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    which_builtin *self = (which_builtin *) parent;

    object_unref((object *) self->args);

    builtin_finalize(parent);
}
