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

void parser_parse_pipe(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);

    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_PIPE)
        THROW(PREMATURE_END_ERR);
    instruction *instr = instruction_new(INSTRUCTION_PIPE);
    parser_add_statement_on_ast(self, instr, FALSE);
    object_unref((object *) instr);
    object_unref((object *) token_);
}

void parser_parse_out_redirection_truncate(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_SIMPLE_RIGHT_CHEVRON)
        THROW(PREMATURE_END_ERR);
    string *destination = parser_parse_text(self);
    instruction *instr1 = instruction_new(INSTRUCTION_OUT_REDIRECTION_TRUNCATE);
    instruction *instr2 = (instruction *) text_new(destination);
    parser_add_statement_on_ast(self, instr1, FALSE);
    parser_add_statement_on_ast(self, instr2, TRUE);
    object_unref((object *) instr1);
    object_unref((object *) instr2);
    object_unref((object *) destination);
    object_unref((object *) token_);
}

void parser_parse_out_redirection_append(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_DOUBLE_RIGHT_CHEVRON)
        THROW(PREMATURE_END_ERR);
    string *destination = parser_parse_text(self);
    instruction *instr1 = instruction_new(INSTRUCTION_OUT_REDIRECTION_APPEND);
    instruction *instr2 = (instruction *) text_new(destination);
    parser_add_statement_on_ast(self, instr1, FALSE);
    parser_add_statement_on_ast(self, instr2, TRUE);
    object_unref((object *) instr1);
    object_unref((object *) instr2);
    object_unref((object *) destination);
    object_unref((object *) token_);
}

void parser_parse_in_redirection_file(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_SIMPLE_LEFT_CHEVRON)
        THROW(PREMATURE_END_ERR);
    string *destination = parser_parse_text(self);
    instruction *instr1 = instruction_new(INSTRUCTION_IN_REDIRECTION_FILE);
    instruction *instr2 = (instruction *) text_new(destination);
    parser_add_statement_on_ast(self, instr1, FALSE);
    parser_add_statement_on_ast(self, instr2, TRUE);
    object_unref((object *) instr1);
    object_unref((object *) instr2);
    object_unref((object *) destination);
    object_unref((object *) token_);
}

void parser_parse_in_redirection_read(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_pop_whitespace(self);
    list *tokens = self->tokens;
    token *token_ = (token *) list_pop_head(tokens);
    if (token_->type == TOKEN_EOF)
        THROW(PREMATURE_END_ERR);
    if (token_->type != TOKEN_DOUBLE_LEFT_CHEVRON)
        THROW(PREMATURE_END_ERR);
    string *destination = parser_parse_text(self);
    instruction *instr1 = instruction_new(INSTRUCTION_IN_REDIRECTION_READ);
    instruction *instr2 = (instruction *) text_new(destination);
    parser_add_statement_on_ast(self, instr1, FALSE);
    parser_add_statement_on_ast(self, instr2, TRUE);
    object_unref((object *) instr1);
    object_unref((object *) instr2);
    object_unref((object *) destination);
    object_unref((object *) token_);
}
