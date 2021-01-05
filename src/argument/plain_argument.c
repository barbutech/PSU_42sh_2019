/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The plain_argument class.
*/

#include "argument/plain_argument.h"
#include "argument/argument.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

plain_argument *plain_argument_construct(type *object_type)
{
    plain_argument *self = (plain_argument *) argument_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &plain_argument_finalize;

    return (self);
}

plain_argument *plain_argument_new(string *content)
{
    plain_argument *self = plain_argument_construct(TYPE_PLAIN_ARGUMENT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) content);

    self->content = content;
    ((argument *) self)->get_content = &plain_argument_get_content;

    return (self);
}

string *plain_argument_get_content(argument *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);
    plain_argument *self = (plain_argument *) parent;

    object_ref((object *) self->content);

    return (self->content);
}

type *plain_argument_get_type(void)
{
    return (type_register(
        "argument.plain_argument",
        sizeof(plain_argument),
        TYPE_ARGUMENT
    ));
}

void plain_argument_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    plain_argument *self = (plain_argument *) parent;

    object_unref((object *) self->content);

    argument_finalize(parent);
}
