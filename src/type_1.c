/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The type utility.
*/

#include <stdlib.h>
#include "lang/object.h"
#include "type.h"
#include "base.h"

void *type_instantiate(type *object_type)
{
    RETURN_VAL_IF_FAIL(object_type != NULL, NULL);

    uint size = type_get_size(object_type);

    return (malloc(size));
}

uint type_get_size(type *object_type)
{
    RETURN_VAL_IF_FAIL(object_type != NULL, 0);

    uint size = object_type->size;

    if (object_type->parent != NULL)
        size += type_get_size(object_type->parent);

    return (size);
}

void type_free(type *object_type)
{
    RETURN_IF_FAIL(object_type != NULL);

    if (object_type->parent != NULL)
        type_free(object_type->parent);

    free(object_type);
}

type *type_register(char *name, uint size, type *parent)
{
    type *object_type = malloc(sizeof(type));
    RETURN_VAL_IF_FAIL(object_type != NULL, NULL);

    object_type->name = name;
    object_type->size = size;
    object_type->parent = parent;

    return (object_type);
}
