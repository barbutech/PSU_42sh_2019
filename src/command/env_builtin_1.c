/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The env_builtin class.
*/

#include "command/env_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "env/environment.h"
#include "util/entry.h"
#include "util/node.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

env_builtin *env_builtin_construct(type *object_type)
{
    env_builtin *self = (env_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &env_builtin_finalize;

    return (self);
}

env_builtin *env_builtin_new(environment *environment)
{
    env_builtin *self = env_builtin_construct(TYPE_ENV_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->environment = environment;

    ((builtin *) self)->execute = &env_builtin_execute;
    ((builtin *) self)->is = &env_builtin_is;

    return (self);
}

type *env_builtin_get_type(void)
{
    return (type_register(
        "command.env_builtin",
        sizeof(env_builtin),
        TYPE_BUILTIN
    ));
}

void env_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);

    builtin_finalize(parent);
}
