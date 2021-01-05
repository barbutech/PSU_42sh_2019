/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The builtin abstract class header.
*/

#ifndef BUILTIN_H
#define BUILTIN_H

#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct builtin builtin;

struct builtin {
    object parent;
    bool (*prepare)(builtin *self, list *arguments);
    bool (*execute)(builtin *self);
    void (*dispose)(builtin *self);
    bool (*is)(builtin *self, string *name);
};

#define TYPE_BUILTIN (builtin_get_type())

builtin *builtin_construct(type *object_type);
bool builtin_prepare(builtin *self, list *arguments);
bool builtin_execute(builtin *self);
void builtin_dispose(builtin *self);
bool builtin_is(builtin *self, string *name);
type *builtin_get_type(void);
void builtin_finalize(object *parent);

#endif
