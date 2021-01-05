/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The tokenized_argument class header.
*/

#ifndef TOKENIZED_ARGUMENT_H
#define TOKENIZED_ARGUMENT_H

#include "argument/argument.h"
#include "command/command_manager.h"
#include "var/variable_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct tokenized_argument tokenized_argument;

struct tokenized_argument {
    argument parent;
    list *tokens;
    command_manager *cmd_manager;
    variable_manager *var_manager;
};

#define TYPE_TOKENIZED_ARGUMENT (tokenized_argument_get_type())

#define TOK_ARG_GET_CONTENT \
if ((pid = fork()) == -1) { \
    THROW(SYSCALL_ERR); \
} else if (pid == 0) { \
    close(fd[0]); \
    dup2(fd[1], 1); \
    parser *parser_ = parser_new_from_token_list( \
        self->tokens, self->cmd_manager, self->var_manager); \
    parser_parse(parser_); \
    interpreter *interpreter_ = interpreter_new( \
        parser_, self->cmd_manager, self->var_manager); \
    interpreter_interprete(interpreter_); \
    object_unref((object *) parser_); \
    object_unref((object *) interpreter_); \
    close(fd[1]); \
    exit(1); \
} else { \
    close(fd[1]); \
    int len; \
    char buffer[2000]; \
    while ((len = read(fd[0], buffer, 1999)) > 0) { \
        string *tmp = string_new_with_length(buffer, len); \
        string *tmp2 = string_add(content, tmp); \
        object_unref((object *) content); \
        object_unref((object *) tmp); \
        content = tmp2; \
    } \
    close(fd[0]); \
}

tokenized_argument *tokenized_argument_construct(type *object_type);
tokenized_argument *tokenized_argument_new(
    list *tokens, command_manager *cmd_manager, variable_manager *var_manager
);
string *tokenized_argument_get_content(argument *parent);
type *tokenized_argument_get_type(void);
void tokenized_argument_finalize(object *parent);

#endif
