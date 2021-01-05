/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The stack class.
*/

#include "util/stack.h"
#include "lang/object.h"
#include "util/list.h"
#include "util/node.h"
#include "type.h"
#include "base.h"

stack *stack_construct(type *object_type)
{
    stack *self = (stack *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &stack_finalize;

    return (self);
}

stack *stack_new(void)
{
    stack *self = stack_construct(TYPE_STACK);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->list = list_new();

    return (self);
}

type *stack_get_type(void)
{
    return (type_register(
        "util.stack",
        sizeof(stack),
        TYPE_OBJECT
    ));
}

void stack_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    stack *self = (stack *) parent;

    object_unref((object *) self->list);

    object_finalize(parent);
}
