/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The argument abstract class header.
*/

#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct argument argument;

struct argument {
    object parent;
    string *(*get_content)(argument *self);
    bool (*is_accessible)(argument *self);
};

#define TYPE_ARGUMENT (argument_get_type())

argument *argument_construct(type *object_type);
string *argument_get_content(argument *self);
bool argument_is_accessible(argument *self);
type *argument_get_type(void);
void argument_finalize(object *parent);

#endif
