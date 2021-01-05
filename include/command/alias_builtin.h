/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias_builtin.h
*/

#ifndef ALIAS_BUILTIN_H
#define ALIAS_BUILTIN_H

#include "base.h"
#include "type.h"
#include "io/console.h"
#include "command/builtin.h"
#include "argument/argument.h"
#include "util/map.h"
#include "aliases/alias.h"

typedef struct alias_builtin alias_builtin;

struct alias_builtin
{
    builtin parent;
    map *map;
    list *arguments;
    alias *alias;
};

#define TYPE_ALIAS_BUILTIN (alias_builtin_get_type())

#define ALIAS_BUILTIN_EXEC \
if (self->arguments->size == 0) { \
    RETURN_VAL_IF_FAIL(self->alias->map->list->head != NULL, TRUE); \
    node *tmp = self->alias->map->list->head; \
    while (tmp) { \
        entry *entry_ = (entry *) tmp->value; \
        string *key = (string *) entry_->key; \
        string *value = (string *) entry_->value; \
        console_writeln("%S=%S", key, value); \
        tmp = tmp->next; \
    } \
} else { \
    node *tmp = self->arguments->head; \
    while (tmp) { \
        string *arg = (string *) tmp->value; \
        tmp = tmp->next; \
        string *value = (string *) tmp->value; \
        alias_set(self->alias, arg, value); \
        tmp = tmp->next; \
    } \
}

alias_builtin *alias_builtin_construct(type *object_type);
alias_builtin *alias_builtin_new(alias *alias);
bool alias_builtin_prepare(builtin *parent, list *arguments);
bool alias_builtin_execute(builtin *parent);
bool alias_builtin_is(builtin *parent, string *name);
type *alias_builtin_get_type(void);
void alias_builtin_finalize(object *parent);
bool contains_non_alphanum(string *str);
bool is_alphanum(char c);
bool is_num(char c);

#endif
