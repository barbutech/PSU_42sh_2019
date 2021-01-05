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

void lexer_lexe(lexer *self)
{
    RETURN_IF_FAIL(self != NULL);

    token *token_;
    self->pos = 0;

    while ((token_ = lexer_get_next_token(self)) != NULL) {
        list_push(self->tokens, (object *) token_);
        object_unref((object *) token_);
    }
}

bool is_text(char c)
{
    char not_text[] = {
        '|', '>', '<', '&', ';', '#', '$',
        '"', '\'', '`', ' ', '\t', '\n', '\0'
    };

    if (c < 0)
        return (TRUE);

    if (32 > c || c > 126)
        return (FALSE);

    for (int i = 0; i < 11; i++)
        if (c == not_text[i])
            return (FALSE);

    return (TRUE);
}

bool is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

token *lexer_get_next_token(lexer *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);
    if (self->pos > self->content->length)
        return (NULL);
    int start = self->pos;
    token_type type = TOKEN_UNKNOWN;
    if (is_text(self->content->value[self->pos])) {
        while (is_text(self->content->value[self->pos]))
            self->pos++;
        type = TOKEN_TEXT;
    } else if (is_whitespace(self->content->value[self->pos])) {
        while (is_whitespace(self->content->value[self->pos]))
            self->pos++;
        type = TOKEN_WHITESPACE;
    } else {
        LEXER_GET_NEXT;
    }
    string *substr = string_substring(self->content, start, self->pos);
    token *token_ = token_new(substr, type);
    object_unref((object *) substr);
    return (token_);
}
