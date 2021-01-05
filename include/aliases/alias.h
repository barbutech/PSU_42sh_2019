/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias.h
*/

#ifndef ALIAS_H
#define ALIAS_H

#include "util/map.h"
#include "lang/object.h"
#include "base.h"
#include "type.h"
#include "lang/string.h"
#include "util/entry.h"

typedef struct alias alias;

struct alias
{
    object parent;
    map *map;
};

#define TYPE_ALIAS (alias_get_type())

alias *alias_construct(type *object_type);
alias *alias_new(void);
void alias_finalize(object *parent);
type *alias_get_type(void);
string *alias_is_there_an_alias(alias *self, string *line);
string *alias_replace(alias *self, string *line, string *elem_to_replace);
void alias_set(alias *self, string *key, string *value);
string *alias_get(alias *self, string *key);
bool alias_contains(alias *self, string *key);
void alias_case_unalias(alias *self, string *key);

#endif
