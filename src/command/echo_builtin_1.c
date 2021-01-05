/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** echo_builtin.c
*/

#include "command/builtin.h"
#include "command/echo_builtin.h"

echo_builtin *echo_builtin_construct(type *object_type)
{
    echo_builtin *self = (echo_builtin *) builtin_construct(object_type);

    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &echo_builtin_finalize;
    return (self);
}

echo_builtin *echo_builtin_new(void)
{
    echo_builtin *self = echo_builtin_construct(TYPE_ECHO_BUILTIN);

    RETURN_VAL_IF_FAIL(self != NULL, NULL);
    self->arguments = NULL;

    ((builtin *) self)->is = &echo_builtin_is;
    ((builtin *) self)->execute = &echo_builtin_execute;
    ((builtin *) self)->prepare = &echo_builtin_prepare;
    return (self);
}

type *echo_builtin_get_type(void)
{
    return (type_register(
        "builtin.echo_builtin",
        sizeof(echo_builtin),
        TYPE_BUILTIN
    ));
}

void echo_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    echo_builtin *self = (echo_builtin *) parent;

    object_unref((object *) self->arguments);
    builtin_finalize(parent);
}
