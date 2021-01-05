/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias_init.c
*/

#include "aliases/alias.h"

alias *alias_construct(type *object_type)
{
    alias *self = (alias *) object_construct(object_type);
    ((object *) self)->finalize = &alias_finalize;
    return (self);
}

alias *alias_new(void)
{
    alias *self = alias_construct(TYPE_ALIAS);

    self->map = map_new();
    return (self);
}

type *alias_get_type(void)
{
    return (type_register(
        "aliases.alias",
        sizeof(alias),
        TYPE_OBJECT));
}

void alias_finalize(object *parent)
{
    alias *self = (alias *) parent;
    object_unref((object *) self->map);
    object_finalize(parent);
}
