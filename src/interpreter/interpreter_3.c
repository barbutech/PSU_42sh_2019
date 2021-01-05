/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The interpreter class.
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "interpreter/interpreter.h"
#include "lang/object.h"
#include "parser/parser.h"
#include "instruction/instruction.h"
#include "instruction/command.h"
#include "instruction/text.h"
#include "command/command_manager.h"
#include "var/variable_manager.h"
#include "util/list.h"
#include "io/console.h"
#include "try.h"
#include "type.h"
#include "base.h"

void interpreter_interprete_pipe(interpreter *self, tree *tree_,
    redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    if (instr->type != INSTRUCTION_PIPE)
        THROW(UNEXPECTED_INSTRUCTION_ERR);

    if (tree_->left == NULL || tree_->right == NULL)
        THROW(INVALID_NULL_CMD_ERR);

    interpreter_interprete_statement(self, tree_->left, REDIRECT_WRITE);
    interpreter_interprete_statement(self, tree_->right,
        redirect != REDIRECT_STANDARD ? REDIRECT_WRITE : REDIRECT_READ);
}

void interpreter_interprete_out_redirection_truncate(interpreter *self,
    tree *tree_, redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    if (instr->type != INSTRUCTION_OUT_REDIRECTION_TRUNCATE)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    if (tree_->left == NULL || tree_->right == NULL)
        THROW(PREMATURE_END_ERR);
    if (((instruction *) tree_->right->value)->type != INSTRUCTION_TEXT)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    text *text_ = (text *) tree_->right->value;
    INTERPRETER_OUT_TRUNCATE;
}

void interpreter_interprete_out_redirection_append(interpreter *self,
    tree *tree_, redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    if (instr->type != INSTRUCTION_OUT_REDIRECTION_APPEND)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    if (tree_->left == NULL || tree_->right == NULL)
        THROW(PREMATURE_END_ERR);
    if (((instruction *) tree_->right->value)->type != INSTRUCTION_TEXT)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    text *text_ = (text *) tree_->right->value;
    INTERPRETER_IN_APPEND;
}

void interpreter_interprete_in_redirection_file(interpreter *self,
    tree *tree_, redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    if (instr->type != INSTRUCTION_IN_REDIRECTION_FILE)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    if (tree_->left == NULL || tree_->right == NULL)
        THROW(PREMATURE_END_ERR);
    if (((instruction *) tree_->right->value)->type != INSTRUCTION_TEXT)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    INTERPRETER_IN_FILE;
    interpreter_interprete_statement(self, tree_->left, REDIRECT_READ);
}

void interpreter_interprete_in_redirection_read(interpreter *self,
    tree *tree_, redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    if (instr->type != INSTRUCTION_IN_REDIRECTION_READ)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    if (tree_->left == NULL || tree_->right == NULL)
        THROW(PREMATURE_END_ERR);
    if (((instruction *) tree_->right->value)->type != INSTRUCTION_TEXT)
        THROW(UNEXPECTED_INSTRUCTION_ERR);
    INTERPRETER_IN_READ;
    interpreter_interprete_statement(self, tree_->left, REDIRECT_READ);
}
