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

void parser_parse_params(parser *self, command *command_)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);

    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    PARSER_PARSE_PARAMS;
    object_unref((object *) token_);
}

argument *parser_parse_param_plain_text(parser *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    string *content = NULL;
    switch (token_->type) {
        case TOKEN_TEXT:
            content = parser_parse_text(self);
            break;
        default:
            object_unref((object *) token_);
            THROW(UNEXPECTED_TOKEN_ERR);
    }
    argument *argument_ = (argument *) plain_argument_new(content);
    object_unref((object *) token_);
    object_unref((object *) content);
    return (argument_);
}

argument *parser_parse_param_quote(parser *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_QUOTE && token_->type != TOKEN_DOUBLE_QUOTE)
        THROW(UNEXPECTED_TOKEN_ERR);
    token_type quote_type = token_->type;
    object_unref((object *) token_);
    token_ = (token *) list_pop_head(tokens);
    string *content = string_new("");
    PARSER_PARSE_PARAMS_QUOTE;
    argument *argument_ = (argument *) plain_argument_new(content);
    object_unref((object *) token_);
    object_unref((object *) content);

    return (argument_);
}

argument *parser_parse_param_backtick(parser *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    parser_pop_whitespace(self);
    PARSER_PARSE_PARAMS_BACKTICK;
    return (argument_);
}

argument *parser_parse_param_variable(parser *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_DOLLAR)
        THROW(UNEXPECTED_TOKEN_ERR);
    string *var_name = parser_parse_text(self);
    argument *argument_ =
    (argument *) variable_argument_new(var_name, self->var_manager);
    object_unref((object *) token_);
    object_unref((object *) var_name);

    return (argument_);
}
