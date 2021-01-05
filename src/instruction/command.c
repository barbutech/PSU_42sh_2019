/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The command class.
*/

#include "instruction/command.h"
#include "instruction/instruction.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

command *command_construct(type *object_type)
{
    command *self = (command *) instruction_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &command_finalize;

    return (self);
}

command *command_new(string *name)
{
    command *self = command_construct(TYPE_COMMAND);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) name);

    self->name = name;
    self->arguments = list_new();

    ((instruction *) self)->type = INSTRUCTION_COMMAND;

    return (self);
}

type *command_get_type(void)
{
    return (type_register(
        "instruction.command",
        sizeof(command),
        TYPE_INSTRUCTION
    ));
}

void command_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    command *self = (command *) parent;

    object_unref((object *) self->name);
    object_unref((object *) self->arguments);

    instruction_finalize(parent);
}
