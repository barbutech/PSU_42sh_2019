/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The token class header.
*/

#ifndef TOKEN_H
#define TOKEN_H

#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct token token;
typedef enum token_type token_type;

enum token_type {
    TOKEN_WHITESPACE,
    TOKEN_TEXT,
    TOKEN_SEMICOLON,
    TOKEN_QUOTE,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_BACKTICK,
    TOKEN_PIPE,
    TOKEN_SIMPLE_LEFT_CHEVRON,
    TOKEN_DOUBLE_LEFT_CHEVRON,
    TOKEN_SIMPLE_RIGHT_CHEVRON,
    TOKEN_DOUBLE_RIGHT_CHEVRON,
    TOKEN_DOLLAR,
    TOKEN_HASH,
    TOKEN_EOL,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
    TOKEN_OR,
    TOKEN_AND
};

struct token {
    object parent;
    string *content;
    token_type type;
};

#define TYPE_TOKEN (token_get_type())

token *token_construct(type *object_type);
token *token_new(string *content, token_type type);
type *token_get_type(void);
void token_finalize(object *parent);

#endif
