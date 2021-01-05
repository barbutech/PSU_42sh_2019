/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** echo_builtin.h
*/

#ifndef ECHO_BUILTIN_H
#define ECHO_BUILTIN_H

#include "base.h"
#include "type.h"
#include "io/console.h"
#include "command/builtin.h"
#include "util/list.h"

typedef struct echo_builtin echo_builtin;

struct echo_builtin
{
    builtin parent;
    list *arguments;
};

#define TYPE_ECHO_BUILTIN (echo_builtin_get_type())

echo_builtin *echo_builtin_construct(type *object_type);
echo_builtin *echo_builtin_new(void);
bool echo_builtin_prepare(builtin *parent, list *arguments);
bool echo_builtin_execute(builtin *parent);
bool echo_builtin_is(builtin *parent, string *name);
type *echo_builtin_get_type(void);
void echo_builtin_finalize(object *parent);

#endif
