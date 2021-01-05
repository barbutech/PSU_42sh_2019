/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The lexer class header.
*/

#ifndef LEXER_H
#define LEXER_H

#include "lang/object.h"
#include "lang/string.h"
#include "lexer/token.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct lexer lexer;

struct lexer {
    object parent;
    string *content;
    list *tokens;
    int pos;
};

#define TYPE_LEXER (lexer_get_type())

#define LEXER_GET_NEXT \
switch (self->content->value[self->pos]) { \
    case ';': \
        type = TOKEN_SEMICOLON; \
        break; \
    case '>': \
        if (self->content->value[self->pos + 1] != '>') { \
            type = TOKEN_SIMPLE_RIGHT_CHEVRON; \
        } else { \
            type = TOKEN_DOUBLE_RIGHT_CHEVRON; \
            self->pos++; \
        } \
        break; \
    case '<': \
        if (self->content->value[self->pos + 1] != '<') { \
            type = TOKEN_SIMPLE_LEFT_CHEVRON; \
        } else { \
            type = TOKEN_DOUBLE_LEFT_CHEVRON; \
            self->pos++; \
        } \
        break; \
    case '|': \
        if (self->content->value[self->pos + 1] == '|') { \
            self->pos++; \
            type = TOKEN_OR; \
            break; \
        } else \
            type = TOKEN_PIPE; \
        break; \
    case '#': \
        type = TOKEN_HASH; \
        break; \
    case '$': \
        type = TOKEN_DOLLAR; \
        break; \
    case '\'': \
        type = TOKEN_QUOTE; \
        break; \
    case '"': \
        type = TOKEN_DOUBLE_QUOTE; \
        break; \
    case '`': \
        type = TOKEN_BACKTICK; \
        break; \
    case '\n': \
        type = TOKEN_EOL; \
        break; \
    case '\0': \
        type = TOKEN_EOF; \
        break; \
    case '&': \
        if (self->content->value[self->pos + 1] == '&') { \
            self->pos++; \
            type = TOKEN_AND; \
            break; \
        } \
    default: \
        type = TOKEN_UNKNOWN; \
} \
self->pos++;

lexer *lexer_construct(type *object_type);
lexer *lexer_new(string *content);
void lexer_lexe(lexer *self);
token *lexer_get_next_token(lexer *self);
type *lexer_get_type(void);
void lexer_finalize(object *parent);

#endif
