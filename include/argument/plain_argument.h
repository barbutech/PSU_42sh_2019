/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The plain_argument class header.
*/

#ifndef PLAIN_ARGUMENT_H
#define PLAIN_ARGUMENT_H

#include "argument/argument.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct plain_argument plain_argument;

struct plain_argument {
    argument parent;
    string *content;
};

#define TYPE_PLAIN_ARGUMENT (plain_argument_get_type())

plain_argument *plain_argument_construct(type *object_type);
plain_argument *plain_argument_new(string *content);
string *plain_argument_get_content(argument *parent);
type *plain_argument_get_type(void);
void plain_argument_finalize(object *parent);

#endif
