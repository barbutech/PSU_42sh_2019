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

string *parser_parse_text(parser *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_TEXT)
        THROW(UNEXPECTED_TOKEN_ERR);
    string *content = token_->content;
    object_ref((object *) content);
    object_unref((object *) token_);

    return (content);
}

void parser_parse_comment(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_HASH)
        THROW(UNEXPECTED_TOKEN_ERR);
    object_unref((object *) token_);
    token_ = (token *) list_get_head(tokens);
    while (token_->type != TOKEN_EOL && token_->type != TOKEN_EOF) {
        object_unref((object *) token_);
        token_ = (token *) list_pop_head(tokens);
    }
    object_unref((object *) token_);
}

void parser_parse_continuation(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    while (token_->type == TOKEN_SEMICOLON || token_->type == TOKEN_EOL) {
        list_remove_head(tokens);
        object_unref((object *) token_);
        token_ = (token *) list_get_head(tokens);
    }
    if (token_->type != TOKEN_EOF) {
        parser_merge_trees(self);
    }
    object_unref((object *) token_);
}

void parser_parse_and(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    if (token_->type == TOKEN_AND) {
        list_remove_head(tokens);
        instruction *instr = instruction_new(INSTRUCTION_AND);
        parser_add_statement_on_ast(self, instr, FALSE);
        object_unref((object *) instr);
    }
    object_unref((object *) token_);
}

void parser_parse_or(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);
    if (token_->type == TOKEN_OR) {
        list_remove_head(tokens);
        instruction *instr = instruction_new(INSTRUCTION_OR);
        parser_add_statement_on_ast(self, instr, FALSE);
        object_unref((object *) instr);
    }
    object_unref((object *) token_);
}
