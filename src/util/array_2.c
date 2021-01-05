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

void array_set(array *self, object *elem, int index)
{
    RETURN_IF_FAIL(self != NULL);

    if (index < 0 || index >= self->size)
        return;

    object_unref(self->array[index]);
    object_ref(elem);

    self->array[index] = elem;
}

object *array_get(array *self, int index)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (index < 0 || index >= self->size)
        return (NULL);

    object_ref((object *) self->array[index]);
    return (self->array[index]);
}
