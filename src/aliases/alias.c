/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias.c
*/

#include "aliases/alias.h"

string *alias_is_there_an_alias(alias *self, string *line)
{
    int length = self->map->list->size;

    for (int count = 0; count < length; count++){
        entry *elem = (entry *) list_get_by_index(self->map->list, count);
        if (string_has_prefix(line, (string *) elem->key))
            return ((string *) elem->key);
        object_unref((object *) elem);
    }

    return(NULL);
}

bool alias_contains(alias *self, string *key)
{
    if (map_contains(self->map, (object *) key))
        return (TRUE);
    return (FALSE);
}

void alias_case_unalias(alias *self, string *key)
{
    if (map_contains(self->map, (object *) key))
        map_remove(self->map, (object *) key);
}
