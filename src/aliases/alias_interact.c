/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias_interact.c
*/

#include "aliases/alias.h"

string *alias_replace(alias *self, string *line, string *elem_to_replace)
{
    string *suffix = string_substring(
        line, elem_to_replace->length, line->length
    );

    string *prefix = alias_get(self, elem_to_replace);

    string *final = string_add(prefix, suffix);

    object_unref((object *) suffix);
    object_unref((object *) prefix);

    return (final);
}

void alias_set(alias *self, string *key, string *value)
{
    if (alias_contains(self, key)) {
        map_change(self->map, (object *) key, (object *) value);
        return ;
    }
    map_set(self->map, (object *) key, (object *) value);
}

string *alias_get(alias *self, string *key)
{
    if (map_contains(self->map, (object *) key))
        return ((string *) map_get(self->map, (object *) key));
    return (NULL);
}
