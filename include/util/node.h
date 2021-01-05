/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The node class header.
*/

#ifndef NODE_H
#define NODE_H

#include "lang/object.h"
#include "type.h"
#include "base.h"

typedef struct node node;

struct node {
    object parent;
    object *value;
    node *next;
};

#define TYPE_NODE (node_get_type())

node *node_construct(type *object_type);
node *node_new(object *value);
type *node_get_type(void);
void node_finalize(object *parent);

#endif
