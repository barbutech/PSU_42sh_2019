/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The instruction class.
*/

#include "instruction/instruction.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

instruction *instruction_construct(type *object_type)
{
    instruction *self = (instruction *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &instruction_finalize;

    return (self);
}

instruction *instruction_new(instruction_type type)
{
    instruction *self = instruction_construct(TYPE_INSTRUCTION);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->type = type;

    return (self);
}

type *instruction_get_type(void)
{
    return (type_register(
        "instruction.instruction",
        sizeof(instruction),
        TYPE_OBJECT
    ));
}

void instruction_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    object_finalize(parent);
}
