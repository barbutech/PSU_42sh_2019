/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The repeat_builtin class.
*/

#include "command/repeat_builtin.h"
#include "command/builtin.h"
#include "command/command_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "io/console.h"
#include "argument/argument.h"
#include "argument/plain_argument.h"
#include "type.h"
#include "base.h"

repeat_builtin *repeat_builtin_construct(type *object_type)
{
    repeat_builtin *self = (repeat_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &repeat_builtin_finalize;

    return (self);
}

repeat_builtin *repeat_builtin_new(command_manager *cmd_manager)
{
    repeat_builtin *self = repeat_builtin_construct(TYPE_REPEAT_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->cmd_manager = cmd_manager;

    self->n = 0;
    self->name = NULL;
    self->args = NULL;

    ((builtin *) self)->is = &repeat_builtin_is;
    ((builtin *) self)->execute = &repeat_builtin_execute;
    ((builtin *) self)->prepare = &repeat_builtin_prepare;

    return (self);
}

type *repeat_builtin_get_type(void)
{
    return (type_register(
        "command.repeat_builtin",
        sizeof(repeat_builtin),
        TYPE_BUILTIN
    ));
}

void repeat_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    repeat_builtin *self = (repeat_builtin *) parent;

    object_unref((object *) self->name);
    object_unref((object *) self->args);

    builtin_finalize(parent);
}
