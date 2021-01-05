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

void map_set(map *self, object *key, object *value)
{
    RETURN_IF_FAIL(self != NULL);

    entry *entry_ = entry_new(key, value);
    list_push(self->list, (object *) entry_);

    object_unref((object *) entry_);
}

void map_change(map *self, object *key, object *new_value)
{
    RETURN_IF_FAIL(self != NULL);

    node *tmp = self->list->head;

    while (tmp != NULL) {
        entry *entry_ = (entry *) tmp->value;
        if (object_equals(entry_->key, key)) {
            object_unref((object *) entry_->value);
            object_ref((object *) new_value);
            entry_->value = new_value;
            return;
        }
        tmp = tmp->next;
    }
}

bool map_contains(map *self, object *key)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    node *tmp = self->list->head;

    while (tmp != NULL) {
        entry *entry_ = (entry *) tmp->value;
        if (object_equals(entry_->key, key))
            return (TRUE);
        tmp = tmp->next;
    }
    return (FALSE);
}
