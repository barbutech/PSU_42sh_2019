/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The variable_argument class header.
*/

#ifndef VARIABLE_ARGUMENT_H
#define VARIABLE_ARGUMENT_H

#include "argument/argument.h"
#include "var/variable_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct variable_argument variable_argument;

struct variable_argument {
    argument parent;
    string *var_name;
    variable_manager *var_manager;
};

#define TYPE_VARIABLE_ARGUMENT (variable_argument_get_type())

variable_argument *variable_argument_construct(type *object_type);
variable_argument *variable_argument_new(
    string *var_name, variable_manager *var_manager
);
string *variable_argument_get_content(argument *parent);
bool variable_argument_is_accessible(argument *parent);
type *variable_argument_get_type(void);
void variable_argument_finalize(object *parent);

#endif
