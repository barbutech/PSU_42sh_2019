/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The lexer class.
*/

#include "lexer/lexer.h"
#include "lang/object.h"
#include "lang/string.h"
#include "lexer/token.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

lexer *lexer_construct(type *object_type)
{
    lexer *self = (lexer *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &lexer_finalize;

    return (self);
}

lexer *lexer_new(string *content)
{
    lexer *self = lexer_construct(TYPE_LEXER);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) content);

    self->content = content;
    self->tokens = list_new();
    self->pos = 0;

    return (self);
}

type *lexer_get_type(void)
{
    return (type_register(
        "lexer.lexe",
        sizeof(lexer),
        TYPE_OBJECT
    ));
}

void lexer_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    lexer *self = (lexer *) parent;

    object_unref((object *) self->content);
    object_unref((object *) self->tokens);

    object_finalize(parent);
}
