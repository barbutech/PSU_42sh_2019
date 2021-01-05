/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The node class.
*/

#include "util/node.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

node *node_construct(type *object_type)
{
    node *self = (node *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &node_finalize;

    return (self);
}

node *node_new(object *value)
{
    node *self = node_construct(TYPE_NODE);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) value);

    self->value = value;
    self->next = NULL;

    return (self);
}

type *node_get_type(void)
{
    return (type_register(
        "util.node",
        sizeof(node),
        TYPE_OBJECT
    ));
}

void node_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    node *self = (node *) parent;

    object_unref((object *) self->value);
    object_unref((object *) self->next);

    object_finalize(parent);
}
