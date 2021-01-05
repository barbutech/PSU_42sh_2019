/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The unsetenv_builtin class header.
*/

#ifndef UNSETENV_BUILTIN_H
#define UNSETENV_BUILTIN_H

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "type.h"
#include "base.h"

typedef struct unsetenv_builtin unsetenv_builtin;

struct unsetenv_builtin {
    builtin parent;
    environment *environment;
    list *arguments;
};

#define TYPE_UNSETENV_BUILTIN (unsetenv_builtin_get_type())

unsetenv_builtin *unsetenv_builtin_construct(type *object_type);
unsetenv_builtin *unsetenv_builtin_new(environment *environment);
bool unsetenv_builtin_prepare(builtin *parent, list *arguments);
bool unsetenv_builtin_execute(builtin *parent);
bool unsetenv_builtin_is(builtin *parent, string *name);
type *unsetenv_builtin_get_type(void);
void unsetenv_builtin_finalize(object *parent);

#endif
