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

void interpreter_interprete(interpreter *self)
{
    RETURN_IF_FAIL(self != NULL);

    if (self->statements == NULL)
        return;

    TRY {
        interpreter_interprete_statement(self, self->statements,
            REDIRECT_STANDARD);
    } CATCH (PREMATURE_END_ERR) {
        console_errln("42sh: Premature end.");
    } CATCH (UNKNOWN_INSTRUCTION_ERR) {
        console_errln("42sh: Unknown instruction.");
    } CATCH (UNEXPECTED_INSTRUCTION_ERR) {
        console_errln("42sh: Unexpected instruction.");
    } CATCH (INVALID_NULL_CMD_ERR) {
        console_errln("Invalid null command.");
    } CATCH_OTHERS {
        console_errln("42: Error during interpreting.");
    }
    ETRY;
}

void interpreter_interprete_statement(interpreter *self, tree *tree_,
    redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    INTERPRETER_STATEMENT;
}

void interpreter_interprete_command(interpreter *self, tree *tree_,
    redirection redirect)
{
    RETURN_IF_FAIL(self != NULL);

    instruction *instr = (instruction *) tree_->value;

    if (instr->type != INSTRUCTION_COMMAND)
        THROW(UNEXPECTED_INSTRUCTION_ERR);

    command *command_ = (command *) instr;

    if (!command_manager_call(
        self->cmd_manager, command_->name, command_->arguments, redirect)
    )
        console_errln("%S: Command not found.", command_->name);
}
