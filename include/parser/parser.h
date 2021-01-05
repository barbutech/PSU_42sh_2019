/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The parser class header.
*/

#ifndef PARSER_H
#define PARSER_H

#include "lang/object.h"
#include "lexer/lexer.h"
#include "instruction/instruction.h"
#include "instruction/command.h"
#include "argument/argument.h"
#include "util/list.h"
#include "util/tree.h"
#include "command/command_manager.h"
#include "var/variable_manager.h"
#include "try.h"
#include "type.h"
#include "base.h"

typedef struct parser parser;

struct parser {
    object parent;
    list *tokens;
    tree *statements;
    tree *current_statements;
    command_manager *cmd_manager;
    variable_manager *var_manager;
};

#define TYPE_PARSER (parser_get_type())

#define PARSER_PARSE \
TRY { \
    while (token_ != NULL && token_->type != TOKEN_EOF) { \
        parser_parse_statement(self); \
        object_unref((object *) token_); \
        token_ = (token *) list_get_head(tokens); \
    } \
    parser_merge_trees(self); \
} CATCH (PREMATURE_END_ERR) { \
    console_errln("42sh: Premature end"); \
} CATCH (UNKNOWN_TOKEN_ERR) { \
    console_errln("42sh: Unknown token"); \
} CATCH (UNEXPECTED_TOKEN_ERR) { \
    console_errln("42sh: Unexpected token"); \
} CATCH_OTHERS { \
    console_errln("42: Error during parsing"); \
} \
ETRY;

#define PARSER_PARSE_STATEMENT \
switch (token_->type) { \
    case TOKEN_TEXT: \
        parser_parse_command(self); \
        break; \
    case TOKEN_SEMICOLON: \
    case TOKEN_EOL: \
        parser_parse_continuation(self); \
        break; \
    case TOKEN_PIPE: \
        parser_parse_pipe(self); \
        break; \
    case TOKEN_SIMPLE_RIGHT_CHEVRON: \
        parser_parse_out_redirection_truncate(self); \
        break; \
    case TOKEN_DOUBLE_RIGHT_CHEVRON: \
        parser_parse_out_redirection_append(self); \
        break; \
    case TOKEN_SIMPLE_LEFT_CHEVRON: \
        parser_parse_in_redirection_file(self); \
        break; \
    case TOKEN_DOUBLE_LEFT_CHEVRON: \
        parser_parse_in_redirection_read(self); \
        break; \
    case TOKEN_HASH: \
        parser_parse_comment(self); \
        break; \
    case TOKEN_UNKNOWN: \
        object_unref((object *) token_); \
        THROW(UNKNOWN_TOKEN_ERR); \
    case TOKEN_AND: \
        parser_parse_and(self); \
        break; \
    case TOKEN_OR: \
        parser_parse_or(self); \
        break; \
    default: \
        object_unref((object *) token_); \
        THROW(UNEXPECTED_TOKEN_ERR); \
}

#define PARSER_PARSE_PARAMS \
while ( \
    token_->type == TOKEN_TEXT || token_->type == TOKEN_QUOTE || \
    token_->type == TOKEN_DOUBLE_QUOTE || token_->type == TOKEN_BACKTICK || \
    token_->type == TOKEN_DOLLAR \
) { \
    argument *argument_ = NULL; \
    switch (token_->type) { \
        case TOKEN_TEXT: \
            argument_ = parser_parse_param_plain_text(self); \
            break; \
        case TOKEN_QUOTE: \
        case TOKEN_DOUBLE_QUOTE: \
            argument_ = parser_parse_param_quote(self); \
            break; \
        case TOKEN_BACKTICK: \
            argument_ = parser_parse_param_backtick(self); \
            break; \
        case TOKEN_DOLLAR: \
            argument_ = parser_parse_param_variable(self); \
            break; \
        default: \
            THROW(UNEXPECTED_TOKEN_ERR); \
    } \
    list_push(command_->arguments, (object *) argument_); \
    parser_pop_whitespace(self); \
    object_unref((object *) token_); \
    object_unref((object *) argument_); \
    token_ = (token *) list_get_head(tokens); \
}

#define PARSER_PARSE_PARAMS_QUOTE \
while (token_->type != quote_type) { \
    if (token_->type == TOKEN_EOF || token_->type == TOKEN_EOL) \
        THROW(PREMATURE_END_ERR); \
    string *tmp = string_add(content, token_->content); \
    object_unref((object *) content); \
    content = tmp; \
    object_unref((object *) token_); \
    token_ = (token *) list_pop_head(tokens); \
}

#define PARSER_PARSE_PARAMS_BACKTICK \
list *tokens = self->tokens; \
token *token_ = (token *) list_pop_head(tokens); \
if (token_->type == TOKEN_EOF) \
    THROW(PREMATURE_END_ERR); \
if (token_->type != TOKEN_BACKTICK) \
    THROW(UNEXPECTED_TOKEN_ERR); \
object_unref((object *) token_); \
token_ = (token *) list_pop_head(tokens); \
list *backtick_tokens = list_new(); \
while (token_->type != TOKEN_BACKTICK) { \
    if (token_->type == TOKEN_EOF || token_->type == TOKEN_EOL) \
        THROW(PREMATURE_END_ERR); \
    list_push(backtick_tokens, (object *) token_); \
    object_unref((object *) token_); \
    token_ = (token *) list_pop_head(tokens); \
} \
token *tkn = token_new(NULL, TOKEN_EOF); \
list_push(backtick_tokens, (object *) tkn); \
object_unref((object *) tkn); \
argument *argument_ = (argument *) tokenized_argument_new( \
    backtick_tokens, self->cmd_manager, self->var_manager \
); \
object_unref((object *) token_); \
object_unref((object *) backtick_tokens);

parser *parser_construct(type *object_type);
parser *parser_new(lexer *lexer, command_manager *cmd_manager,
    variable_manager *var_manager);
parser *parser_new_from_token_list(list *tokens,
    command_manager *cmd_manager, variable_manager *var_manager);
void parser_add_statement_on_ast(parser *self,
    instruction *instr, bool is_leaf);
void parser_merge_trees(parser *self);
void parser_pop_whitespace(parser *self);
void parser_parse(parser *self);
void parser_parse_statement(parser *self);
void parser_parse_command(parser *self);
void parser_parse_pipe(parser *self);
void parser_parse_out_redirection_truncate(parser *self);
void parser_parse_out_redirection_append(parser *self);
void parser_parse_in_redirection_file(parser *self);
void parser_parse_in_redirection_read(parser *self);
void parser_parse_params(parser *self, command *command_);
argument *parser_parse_param_plain_text(parser *self);
argument *parser_parse_param_quote(parser *self);
argument *parser_parse_param_backtick(parser *self);
argument *parser_parse_param_variable(parser *self);
string *parser_parse_text(parser *self);
void parser_parse_comment(parser *self);
void parser_parse_continuation(parser *self);
type *parser_get_type(void);
void parser_finalize(object *parent);
void parser_parse_and(parser *self);
void parser_merge_trees_custom(parser *self, instruction_type type);
void parser_parse_or(parser *self);

#endif
