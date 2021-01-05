/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The command class header.
*/

#ifndef COMMAND_H
#define COMMAND_H

#include "instruction/instruction.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct command command;

struct command {
    instruction parent;
    string *name;
    list *arguments;
};

#define TYPE_COMMAND (command_get_type())

command *command_construct(type *object_type);
command *command_new(string *name);
type *command_get_type(void);
void command_finalize(object *parent);

#endif
