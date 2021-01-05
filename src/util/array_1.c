/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The array class.
*/

#include <stdlib.h>
#include "util/array.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

array *array_construct(type *object_type)
{
    array *self = (array *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &array_finalize;

    return (self);
}

array *array_new(int size)
{
    array *self = array_construct(TYPE_ARRAY);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->size = size;
    self->array = malloc(sizeof(object *) * size);

    for (int i = 0; i < size; i++)
        self->array[i] = NULL;

    return (self);
}

type *array_get_type(void)
{
    return (type_register(
        "util.array",
        sizeof(array),
        TYPE_OBJECT
    ));
}

void array_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    array *self = (array *) parent;

    for (int i = 0; i < self->size; i++)
        object_unref((object *) self->array[i]);

    free(self->array);

    object_finalize(parent);
}
