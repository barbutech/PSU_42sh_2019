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

void list_push(list *self, object *elem)
{
    RETURN_IF_FAIL(self != NULL);

    node *node_ = node_new(elem);

    if (self->size == 0) {
        self->head = node_;
        self->size++;
        return;
    }
    node *tmp = self->head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node_;
    self->size++;
}

void list_merge(list *self, list *another)
{
    RETURN_IF_FAIL(self != NULL);

    node *tmp = another->head;
    while (tmp != NULL) {
        list_push(self, tmp->value);
        tmp = tmp->next;
    }
}

object *list_get_head(list *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (self->size == 0)
        return (NULL);

    object *result = self->head->value;

    object_ref(result);
    return (result);
}

object *list_get_by_index(list *self, int index)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (0 < index || index >= self->size)
        return (NULL);

    node *tmp = self->head;

    for (int i = 0; i != index; i++)
        tmp = tmp->next;

    object_ref((object *) tmp->value);
    return (tmp->value);
}

object *list_pop_head(list *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object *result = list_get_head(self);
    list_remove_head(self);

    return (result);
}
