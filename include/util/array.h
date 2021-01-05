/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The array class header.
*/

#ifndef ARRAY_H
#define ARRAY_H

#include "lang/object.h"
#include "type.h"
#include "base.h"

typedef struct array array;

struct array {
    object parent;
    object **array;
    int size;
};

#define TYPE_ARRAY (array_get_type())

array *array_construct(type *object_type);
array *array_new(int size);
void array_set(array *self, object *elem, int index);
object *array_get(array *self, int index);
type *array_get_type(void);
void array_finalize(object *parent);

#endif
