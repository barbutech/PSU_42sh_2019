/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The where_builtin class.
*/

#include <stdlib.h>
#include "command/where_builtin.h"
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

where_builtin *where_builtin_construct(type *object_type)
{
    where_builtin *self = (where_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &where_builtin_finalize;

    return (self);
}

where_builtin *where_builtin_new(command_manager *cmd_manager,
    environment *env, alias *alias)
{
    where_builtin *self = where_builtin_construct(TYPE_WHERE_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->cmd_manager = cmd_manager;
    self->env = env;
    self->alias = alias;

    self->args = NULL;

    ((builtin *) self)->is = &where_builtin_is;
    ((builtin *) self)->execute = &where_builtin_execute;
    ((builtin *) self)->prepare = &where_builtin_prepare;

    return (self);
}

type *where_builtin_get_type(void)
{
    return (type_register(
        "command.where_builtin",
        sizeof(where_builtin),
        TYPE_BUILTIN
    ));
}

void where_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    where_builtin *self = (where_builtin *) parent;

    object_unref((object *) self->args);

    builtin_finalize(parent);
}
