/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The map class.
*/

#include "util/map.h"
#include "lang/object.h"
#include "util/list.h"
#include "util/list.h"
#include "util/entry.h"
#include "type.h"
#include "base.h"


object *map_get(map *self, object *key)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    node *tmp = self->list->head;

    while (tmp != NULL) {
        entry *entry_ = (entry *) tmp->value;
        if (object_equals(entry_->key, key))
            return (entry_get_value(entry_));
        tmp = tmp->next;
    }
    return (NULL);
}

void map_remove(map *self, object *key)
{
    RETURN_IF_FAIL(self != NULL);

    int index = map_get_index_by_key(self, key);

    if (index == -1)
        return;

    list_remove(self->list, index);
}

int map_get_index_by_key(map *self, object *key)
{
    RETURN_VAL_IF_FAIL(self != NULL, -1);

    node *tmp = self->list->head;

    for (int i = 0; tmp != NULL; i++) {
        entry *entry_ = (entry *) tmp->value;
        if (object_equals(entry_->key, key))
            return (i);
        tmp = tmp->next;
    }
    return (-1);
}
