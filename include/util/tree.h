/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The tree class header.
*/

#ifndef TREE_H
#define TREE_H

#include "lang/object.h"
#include "type.h"
#include "base.h"

typedef struct tree tree;

struct tree {
    object parent;
    object *value;
    tree *left;
    tree *right;
};

#define TYPE_TREE (tree_get_type())

tree *tree_construct(type *object_type);
tree *tree_new(object *value);
void tree_set(tree *self, object *left, object *right);
type *tree_get_type(void);
void tree_finalize(object *parent);

#endif
