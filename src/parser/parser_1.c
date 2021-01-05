/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The parser class.
*/

#include "parser/parser.h"
#include "lang/object.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "instruction/instruction.h"
#include "instruction/command.h"
#include "instruction/text.h"
#include "argument/argument.h"
#include "argument/plain_argument.h"
#include "argument/tokenized_argument.h"
#include "argument/variable_argument.h"
#include "interpreter/interpreter.h"
#include "command/command_manager.h"
#include "util/list.h"
#include "io/console.h"
#include "try.h"
#include "type.h"
#include "base.h"

parser *parser_construct(type *object_type)
{
    parser *self = (parser *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &parser_finalize;

    return (self);
}

parser *parser_new(lexer *lexer, command_manager *cmd_manager,
    variable_manager *var_manager)
{
    return (parser_new_from_token_list(
        lexer->tokens, cmd_manager, var_manager)
    );
}

parser *parser_new_from_token_list(list *tokens,
    command_manager *cmd_manager, variable_manager *var_manager)
{
    parser *self = parser_construct(TYPE_PARSER);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) tokens);
    object_ref((object *) cmd_manager);
    object_ref((object *) var_manager);

    self->tokens = tokens;
    self->statements = NULL;
    self->current_statements = NULL;
    self->cmd_manager = cmd_manager;
    self->var_manager = var_manager;

    return (self);
}

type *parser_get_type(void)
{
    return (type_register(
        "parser.parser",
        sizeof(parser),
        TYPE_OBJECT
    ));
}

void parser_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    parser *self = (parser *) parent;

    object_unref((object *) self->tokens);
    object_unref((object *) self->statements);
    object_unref((object *) self->current_statements);
    object_unref((object *) self->var_manager);
    object_unref((object *) self->cmd_manager);

    object_finalize(parent);
}
