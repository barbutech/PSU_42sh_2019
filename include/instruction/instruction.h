/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The instruction class header.
*/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "lang/object.h"
#include "type.h"
#include "base.h"

typedef struct instruction instruction;
typedef enum instruction_type instruction_type;

enum instruction_type {
    INSTRUCTION_COMMAND,
    INSTRUCTION_TEXT,
    INSTRUCTION_CONTINUATION,
    INSTRUCTION_PIPE,
    INSTRUCTION_OUT_REDIRECTION_TRUNCATE,
    INSTRUCTION_OUT_REDIRECTION_APPEND,
    INSTRUCTION_IN_REDIRECTION_FILE,
    INSTRUCTION_IN_REDIRECTION_READ,
    INSTRUCTION_AND,
    INSTRUCTION_OR
};

struct instruction {
    object parent;
    instruction_type type;
};

#define TYPE_INSTRUCTION (instruction_get_type())

instruction *instruction_construct(type *object_type);
instruction *instruction_new(instruction_type type);
type *instruction_get_type(void);
void instruction_finalize(object *parent);

#endif
