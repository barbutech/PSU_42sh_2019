/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The list class.
*/

#include "util/list.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/node.h"
#include "type.h"
#include "base.h"

void list_remove_head(list *self)
{
    RETURN_IF_FAIL(self != NULL);

    if (self->size == 0)
        return;

    node *tmp = self->head->next;
    object_ref((object *) tmp);

    object_unref((object *) self->head);
    self->head = tmp;

    self->size--;
}

void list_remove(list *self, int index)
{
    RETURN_IF_FAIL(self != NULL);

    if (index < 0 || index >= self->size)
        return;
    if (index == 0) {
        list_remove_head(self);
        return;
    }
    node *tmp = self->head->next;
    node *prev = self->head;
    for (int i = 1; i < index; i++) {
        prev = tmp;
        tmp = tmp->next;
    }
    self->size--;
    prev->next = tmp->next;

    object_ref((object *) tmp->next);
    object_unref((object *) tmp);
}

void list_clear(list *self)
{
    RETURN_IF_FAIL(self != NULL);

    object_unref((object *) self->head);
    self->size = 0;
}

string *list_join(list *self, string *glue, bool glue_first)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *str = string_new("");
    node *node_ = self->head;
    if (glue_first) {
        string *tmp = string_add(str, glue);
        object_unref((object *) str);
        str = tmp;
    }
    LIST_JOIN;
    return (str);
}
