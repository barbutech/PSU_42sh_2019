/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The list class header.
*/

#ifndef LIST_H
#define LIST_H

#include "lang/object.h"
#include "util/node.h"
#include "type.h"
#include "base.h"

typedef struct list list;

struct list {
    object parent;
    node *head;
    int size;
};

#define TYPE_LIST (list_get_type())

#define LIST_JOIN \
while (node_ != NULL) { \
    string *stringified = object_stringify((object *) node_->value); \
    string *tmp = string_add(str, stringified); \
    object_unref((object *) str); \
    str = tmp; \
    if (node_->next != NULL) { \
        string *tmp = string_add(str, glue); \
        object_unref((object *) str); \
        str = tmp; \
    } \
    object_unref((object *) stringified); \
    node_ = node_->next; \
}

list *list_construct(type *object_type);
list *list_new(void);
void list_push(list *self, object *elem);
void list_merge(list *self, list *another);
object *list_get_head(list *self);
object *list_get_by_index(list *self, int index);
object *list_pop_head(list *self);
void list_remove_head(list *self);
void list_remove(list *self, int index);
void list_clear(list *self);
string *list_join(list *self, string *glue, bool glue_first);
type *list_get_type(void);
void list_finalize(object *parent);

#endif
