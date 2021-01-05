/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The argument abstract class.
*/

#include "argument/argument.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

argument *argument_construct(type *object_type)
{
    argument *self = (argument *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->get_content = NULL;

    ((object *) self)->finalize = &argument_finalize;

    self->get_content = NULL;
    self->is_accessible = NULL;

    return (self);
}

string *argument_get_content(argument *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (self->get_content == NULL)
        return (NULL);

    return (self->get_content(self));
}

bool argument_is_accessible(argument *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, TRUE);

    if (self->is_accessible == NULL)
        return (TRUE);

    return (self->is_accessible(self));
}

type *argument_get_type(void)
{
    return (type_register(
        "argument.argument",
        sizeof(argument),
        TYPE_OBJECT
    ));
}

void argument_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    object_finalize(parent);
}
