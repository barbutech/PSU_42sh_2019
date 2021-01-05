/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The token class.
*/

#include "lexer/token.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

token *token_construct(type *object_type)
{
    token *self = (token *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &token_finalize;

    return (self);
}

token *token_new(string *content, token_type type)
{
    token *self = token_construct(TYPE_TOKEN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) content);

    self->content = content;
    self->type = type;

    return (self);
}

type *token_get_type(void)
{
    return (type_register(
        "lexer.token",
        sizeof(token),
        TYPE_OBJECT
    ));
}

void token_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    token *self = (token *) parent;

    object_unref((object *) self->content);

    object_finalize(parent);
}
