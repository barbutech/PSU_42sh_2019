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

list *list_construct(type *object_type)
{
    list *self = (list *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &list_finalize;

    return (self);
}

list *list_new(void)
{
    list *self = list_construct(TYPE_LIST);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->head = NULL;
    self->size = 0;

    return (self);
}

type *list_get_type(void)
{
    return (type_register(
        "util.list",
        sizeof(list),
        TYPE_OBJECT
    ));
}

void list_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    list *self = (list *) parent;

    object_unref((object *) self->head);

    object_finalize(parent);
}
