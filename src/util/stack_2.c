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

void stack_push(stack *self, object *elem)
{
    RETURN_IF_FAIL(self != NULL);

    list_push(self->list, elem);
}

object *stack_pop(stack *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (self->list->size == 0)
        return (NULL);

    object *elem = list_get_by_index(self->list, self->list->size - 1);
    list_remove(self->list, self->list->size - 1);

    return (elem);
}

bool stack_is_empty(stack *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, TRUE);

    return (self->list->size == 0);
}
