/*
** EPITECH PROJECT, 2019
** test
** File description:
** set_var_builtin.h
*/

#ifndef SETVAR_BUILTIN_H
#define SETVAR_BUILTIN_H

#include "command/builtin.h"
#include "var/variable_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "type.h"
#include "base.h"

typedef struct setvar_builtin setvar_builtin;

struct setvar_builtin {
    builtin parent;
    variable_manager *variable_manager;
    string *key;
    string *value;
};

#define TYPE_SETVAR_BUILTIN (setvar_builtin_get_type())

#define SETVAR_BUILTIN_PREPARE \
if (arguments->size < 1) { \
    console_errln("setvar: Too few arguments."); \
    return (FALSE); \
} \
if (arguments->size > 2) { \
    console_errln("setvar: Too many arguments."); \
    return (FALSE); \
} \
object_unref((object *) self->key); \
object_unref((object *) self->value); \
self->key = (string *) arguments->head->value; \
object_ref((object *) self->key); \
if (arguments->size == 2) { \
    self->value = (string *) arguments->head->next->value; \
    object_ref((object *) self->value); \
} else { \
    self->value = string_new(""); \
} \
if (!is_alpha(self->key->value[0])) { \
    console_errln("setvar: Variable name must begin with a letter."); \
    return (FALSE); \
} \
if (contains_non_alphanum(self->key)) { \
    console_errln( \
        "setvar: Variable name must contain alphanumeric characters."); \
    return (FALSE); \
}

setvar_builtin *setvar_builtin_construct(type *object_type);
setvar_builtin *setvar_builtin_new(variable_manager *var_man);
bool setvar_builtin_prepare(builtin *parent, list *arguments);
bool setvar_builtin_execute(builtin *parent);
bool setvar_builtin_is(builtin *parent, string *name);
type *setvar_builtin_get_type(void);
void setvar_builtin_finalize(object *parent);
bool is_alpha(char c);
bool is_num(char c);
bool is_alphanum(char c);
bool contains_non_alphanum(string *str);

#endif
