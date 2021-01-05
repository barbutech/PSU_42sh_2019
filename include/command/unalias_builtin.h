/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** unalias_builtin.h
*/

#ifndef UNALIAS_BUILTIN_H
#define UNALIAS_BUILTIN_H

#include "base.h"
#include "type.h"
#include "io/console.h"
#include "command/builtin.h"
#include "argument/argument.h"
#include "util/map.h"
#include "aliases/alias.h"

typedef struct unalias_builtin unalias_builtin;

struct unalias_builtin
{
    builtin parent;
    map *map;
    list *arguments;
    alias *alias;
};

#define TYPE_UNALIAS_BUILTIN (unalias_builtin_get_type())

unalias_builtin *unalias_builtin_construct(type *object_type);
unalias_builtin *unalias_builtin_new(alias *alias);
bool unalias_builtin_prepare(builtin *parent, list *arguments);
bool unalias_builtin_execute(builtin *parent);
bool unalias_builtin_is(builtin *parent, string *name);
type *unalias_builtin_get_type(void);
void unalias_builtin_finalize(object *parent);

#endif