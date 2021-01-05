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

void interpreter_interprete_continuation(interpreter *self, tree *tree_)
{
    RETURN_IF_FAIL(self != NULL);

    if (tree_->left != NULL)
        interpreter_interprete_statement(self, tree_->left, REDIRECT_STANDARD);

    if (tree_->right != NULL)
        interpreter_interprete_statement(self, tree_->right, REDIRECT_STANDARD);

}

void interpreter_interprete_and(interpreter *self, tree *tree_)
{
    RETURN_IF_FAIL(self != NULL);

    if (tree_->left != NULL)
        interpreter_interprete_statement(self, tree_->left, REDIRECT_STANDARD);

    if (tree_->right != NULL &&
        self->cmd_manager->shell->last_return_value == 0)
        interpreter_interprete_statement(self, tree_->right, REDIRECT_STANDARD);
}

void interpreter_interprete_or(interpreter *self, tree *tree_)
{
    RETURN_IF_FAIL(self != NULL);

    if (tree_->left != NULL)
        interpreter_interprete_statement(self, tree_->left, REDIRECT_STANDARD);

    if (tree_->right != NULL &&
        self->cmd_manager->shell->last_return_value == 1)
        interpreter_interprete_statement(self, tree_->right, REDIRECT_STANDARD);
}
