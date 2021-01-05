/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The stack class header.
*/

#ifndef STACK_H
#define STACK_H

#include "lang/object.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct stack stack;

struct stack {
    object parent;
    list *list;
};

#define TYPE_STACK (stack_get_type())

stack *stack_construct(type *object_type);
stack *stack_new(void);
void stack_push(stack *self, object *elem);
object *stack_pop(stack *self);
bool stack_is_empty(stack *self);
type *stack_get_type(void);
void stack_finalize(object *parent);

#endif
