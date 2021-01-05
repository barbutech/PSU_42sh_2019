/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The tokenized_argument class.
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "argument/tokenized_argument.h"
#include "argument/argument.h"
#include "command/command_manager.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "try.h"
#include "type.h"
#include "base.h"

tokenized_argument *tokenized_argument_construct(type *object_type)
{
    tokenized_argument *self = (tokenized_argument *)
        argument_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &tokenized_argument_finalize;

    return (self);
}

tokenized_argument *tokenized_argument_new(
    list *tokens, command_manager *cmd_manager, variable_manager *var_manager)
{
    tokenized_argument *self =
        tokenized_argument_construct(TYPE_TOKENIZED_ARGUMENT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) tokens);
    object_ref((object *) cmd_manager);
    object_ref((object *) var_manager);

    self->tokens = tokens;
    self->cmd_manager = cmd_manager;
    self->var_manager = var_manager;

    ((argument *) self)->get_content = &tokenized_argument_get_content;

    return (self);
}

string *tokenized_argument_get_content(argument *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);
    tokenized_argument *self = (tokenized_argument *) parent;
    string *content = string_new("");
    int fd[2];
    pid_t pid;
    pipe(fd);
    TOK_ARG_GET_CONTENT;
    string *tmp = string_substring(content, 0, content->length - 1);
    object_unref((object *) content);
    content = tmp;
    return (content);
}

type *tokenized_argument_get_type(void)
{
    return (type_register(
        "argument.tokenized_argument",
        sizeof(tokenized_argument),
        TYPE_ARGUMENT
    ));
}

void tokenized_argument_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    tokenized_argument *self = (tokenized_argument *) parent;

    object_unref((object *) self->tokens);
    object_unref((object *) self->cmd_manager);
    object_unref((object *) self->var_manager);

    argument_finalize(parent);
}
