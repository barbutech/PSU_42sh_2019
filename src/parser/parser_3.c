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

void parser_parse(parser *self)
{
    RETURN_IF_FAIL(self != NULL);
    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    PARSER_PARSE;
    object_unref((object *) token_);
}

void parser_parse_statement(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);

    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    PARSER_PARSE_STATEMENT;
    object_unref((object *) token_);
}

void parser_parse_command(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);

    string *name = parser_parse_text(self);
    command *command_ = command_new(name);

    parser_add_statement_on_ast(self, (instruction *) command_, TRUE);
    parser_parse_params(self, command_);

    object_unref((object *) command_);
    object_unref((object *) name);
}
