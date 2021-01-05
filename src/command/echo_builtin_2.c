/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** echo_builtin.c
*/

#include "command/builtin.h"
#include "command/echo_builtin.h"

bool echo_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    echo_builtin *self = (echo_builtin *) parent;

    object_unref((object *)self->arguments);
    self->arguments = arguments;
    object_ref((object *) self->arguments);

    return (TRUE);
}

bool echo_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    echo_builtin *self = (echo_builtin *) parent;
    node *tmp = self->arguments->head;

    RETURN_VAL_IF_FAIL(tmp != NULL, TRUE);

    console_write("%S", (string *) tmp->value);
    tmp = tmp->next;
    while (tmp) {
        console_write(" %S", (string *) tmp->value);
        tmp = tmp->next;
    }
    console_write("\n");

    return (TRUE);
}

bool echo_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("echo");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
