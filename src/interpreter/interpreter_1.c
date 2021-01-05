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

interpreter *interpreter_construct(type *object_type)
{
    interpreter *self = (interpreter *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &interpreter_finalize;

    return (self);
}

interpreter *interpreter_new(parser *parser, command_manager *cmd_manager,
    variable_manager *var_manager)
{
    interpreter *self = interpreter_construct(TYPE_INTERPRETER);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) var_manager);
    object_ref((object *) cmd_manager);
    object_ref((object *) parser->statements);

    self->cmd_manager = cmd_manager;
    self->var_manager = var_manager;
    self->statements = parser->statements;

    return (self);
}

type *interpreter_get_type(void)
{
    return (type_register(
        "interpreter.interpreter",
        sizeof(interpreter),
        TYPE_OBJECT
    ));
}

void interpreter_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    interpreter *self = (interpreter *) parent;

    object_unref((object *) self->cmd_manager);
    object_unref((object *) self->var_manager);
    object_unref((object *) self->statements);

    object_finalize(parent);
}
