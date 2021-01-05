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

void parser_add_statement_on_ast(parser *self,
    instruction *instr, bool is_leaf)
{
    RETURN_IF_FAIL(self != NULL);

    tree *tree_ = tree_new((object *) instr);

    if (!is_leaf) {
        tree_->left = self->current_statements;
        self->current_statements = tree_;
        return;
    }
    if (self->current_statements == NULL)
        self->current_statements = tree_;
    else
        self->current_statements->right = tree_;
}

void parser_merge_trees_custom(parser *self, instruction_type type)
{
    RETURN_IF_FAIL(self != NULL);

    if (self->statements == NULL) {
        self->statements = self->current_statements;
        self->current_statements = NULL;
        return;
    }
    instruction *instr = instruction_new(type);
    tree *tree_ = tree_new((object *) instr);
    tree_->left = self->statements;
    tree_->right = self->current_statements;
    object_ref((object *) tree_);
    self->statements = tree_;
    self->current_statements = NULL;
    object_unref((object *) instr);
    object_unref((object *) tree_);
}

void parser_merge_trees(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    parser_merge_trees_custom(self, INSTRUCTION_CONTINUATION);
}

void parser_pop_whitespace(parser *self)
{
    RETURN_IF_FAIL(self != NULL);

    list *tokens = self->tokens;
    token *token_ = (token *) list_get_head(tokens);

    while (token_->type == TOKEN_WHITESPACE) {
        list_remove_head(tokens);

        object_unref((object *) token_);
        token_ = (token *) list_get_head(tokens);
    }

    object_unref((object *) token_);
}
