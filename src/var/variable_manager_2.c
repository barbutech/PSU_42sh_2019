/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The variable_manager class.
*/

#include "var/variable_manager.h"
#include "env/environment.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/map.h"
#include "type.h"
#include "base.h"

void variable_manager_set(variable_manager *self, string *name, string *value)
{
    RETURN_IF_FAIL(self != NULL);

    if (variable_manager_contains(self, name))
        map_change(self->vars, (object *) name, (object *) value);
    else
        map_set(self->vars, (object *) name, (object *) value);
}

string *variable_manager_get(variable_manager *self, string *name)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (!variable_manager_contains_in_env(self, name))
        return ((string *) map_get(self->vars, (object *) name));

    return (environment_get(self->env, name, NULL));
}

void variable_manager_remove(variable_manager *self, string *name)
{
    RETURN_IF_FAIL(self != NULL);

    if (!variable_manager_contains(self, name))
        return;

    map_remove(self->vars, (object *) name);
}

bool variable_manager_contains(variable_manager *self, string *name)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (variable_manager_contains_in_env(self, name))
        return (TRUE);

    return (map_contains(self->vars, (object *) name));
}

bool variable_manager_contains_in_env(variable_manager *self, string *name)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (environment_contains(self->env, name));
}
