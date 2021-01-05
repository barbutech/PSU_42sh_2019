/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The setenv_builtin class header.
*/

#ifndef SETENV_BUILTIN_H
#define SETENV_BUILTIN_H

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "type.h"
#include "base.h"

typedef struct setenv_builtin setenv_builtin;

struct setenv_builtin {
    builtin parent;
    environment *environment;
    string *key;
    string *value;
};

#define TYPE_SETENV_BUILTIN (setenv_builtin_get_type())

#define SETENV_BUILTIN_PREPARE \
self->key = (string *) arguments->head->value; \
object_ref((object *) self->key); \
if (arguments->size == 2) { \
    self->value = (string *) arguments->head->next->value; \
    object_ref((object *) self->value); \
} else { \
    self->value = string_new(""); \
} \
if (!is_alpha(self->key->value[0])) { \
    console_errln("setenv: Variable name must begin with a letter."); \
    return (FALSE); \
} \
if (contains_non_alphanum(self->key)) { \
    console_errln( \
        "setenv: Variable name must contain alphanumeric characters."); \
    return (FALSE); \
}

setenv_builtin *setenv_builtin_construct(type *object_type);
setenv_builtin *setenv_builtin_new(environment *environment);
bool setenv_builtin_prepare(builtin *parent, list *arguments);
bool setenv_builtin_execute(builtin *parent);
bool setenv_builtin_is(builtin *parent, string *name);
type *setenv_builtin_get_type(void);
void setenv_builtin_finalize(object *parent);
bool is_alpha(char c);
bool is_num(char c);
bool is_alphanum(char c);
bool contains_non_alphanum(string *str);

#endif
