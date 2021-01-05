/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The tree class.
*/

#include "util/tree.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

tree *tree_construct(type *object_type)
{
    tree *self = (tree *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &tree_finalize;

    return (self);
}

tree *tree_new(object *value)
{
    tree *self = tree_construct(TYPE_TREE);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref(value);

    self->value = value;

    self->left = NULL;
    self->right = NULL;

    return (self);
}

void tree_set(tree *self, object *left, object *right)
{
    RETURN_IF_FAIL(self != NULL);

    if (left != NULL) {
        object_unref((object *) left);
        self->left = tree_new(left);
    }

    if (right != NULL) {
        object_unref((object *) right);
        self->right = tree_new(right);
    }
}

type *tree_get_type(void)
{
    return (type_register(
        "util.tree",
        sizeof(tree),
        TYPE_OBJECT
    ));
}

void tree_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    tree *self = (tree *) parent;

    object_unref((object *) self->value);
    object_unref((object *) self->left);
    object_unref((object *) self->right);

    object_finalize(parent);
}
