/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The object abstract class header.
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "type.h"
#include "base.h"

typedef struct object object;
typedef struct string string;

struct string;

struct object {
    uint ref_count;
    type *object_type;
    void (*finalize)(object *self);
    string *(*stringify)(object *self);
    bool (*equals)(object *self, object *another);
};

#define TYPE_OBJECT (object_get_type())

object *object_construct(type *object_type);
void object_ref(object *self);
void object_unref(object *self);
string *object_stringify(object *self);
bool object_equals(object *self, object *another);
type *object_get_type(void);
void object_finalize(object *self);

#endif
