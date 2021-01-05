/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The environment class.
*/

#include <stdlib.h>
#include <unistd.h>
#include "env/environment.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/map.h"
#include "util/node.h"
#include "util/entry.h"
#include "type.h"
#include "base.h"

environment *environment_construct(type *object_type)
{
    environment *self = (environment *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &environment_finalize;

    return (self);
}

environment *environment_new(void)
{
    environment *self = environment_construct(TYPE_ENVIRONMENT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->env = map_new();
    self->array = NULL;

    return (self);
}

type *environment_get_type(void)
{
    return (type_register(
        "env.environment",
        sizeof(environment),
        TYPE_OBJECT
    ));
}

void environment_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    environment *self = (environment *) parent;

    object_unref((object *) self->env);

    for (int i = 0; self->array != NULL && self->array[i] != NULL; i++)
        free(self->array[i]);
    free(self->array);

    object_finalize(parent);
}
