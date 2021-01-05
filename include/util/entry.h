/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The entry class haeder.
*/

#ifndef ENTRY_H
#define ENTRY_H

#include "lang/object.h"
#include "type.h"
#include "base.h"

typedef struct entry entry;

struct entry {
    object parent;
    object *key;
    object *value;
};

#define TYPE_ENTRY (entry_get_type())

entry *entry_construct(type *object_type);
entry *entry_new(object *key, object *value);
object *entry_get_value(entry *self);
type *entry_get_type(void);
void entry_finalize(object *parent);

#endif
