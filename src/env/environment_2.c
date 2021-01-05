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

void environment_set(environment *self, string *name,
    string *value, bool overwrite)
{
    RETURN_IF_FAIL(self != NULL);

    if (map_contains(self->env, (object *) name) && !overwrite)
        return;

    if (map_contains(self->env, (object *) name)) {
        map_change(self->env, (object *) name, (object *) value);
        return;
    }

    map_set(self->env, (object *) name, (object *) value);

    environment_generate_array(self);
}

string *environment_get(environment *self, string *name, string *def)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object *result = map_get(self->env, (object *) name);

    if (result == NULL) {
        object_ref((object *) def);
        return (def);
    }

    return ((string *) result);
}

void environment_remove(environment *self, string *name)
{
    RETURN_IF_FAIL(self != NULL);

    map_remove(self->env, (object *) name);

    environment_generate_array(self);
}

bool environment_contains(environment *self, string *name)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (map_contains(self->env, (object *) name));
}
