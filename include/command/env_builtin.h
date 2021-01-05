/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The env_builtin class header.
*/

#ifndef ENV_BUILTIN_H
#define ENV_BUILTIN_H

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "env/environment.h"
#include "type.h"
#include "base.h"

typedef struct env_builtin env_builtin;

struct env_builtin {
    builtin parent;
    environment *environment;
};

#define TYPE_ENV_BUILTIN (env_builtin_get_type())

env_builtin *env_builtin_construct(type *object_type);
env_builtin *env_builtin_new(environment *environment);
bool env_builtin_execute(builtin *parent);
bool env_builtin_is(builtin *parent, string *name);
type *env_builtin_get_type(void);
void env_builtin_finalize(object *parent);

#endif
