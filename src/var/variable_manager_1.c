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

variable_manager *variable_manager_construct(type *object_type)
{
    variable_manager *self = (variable_manager *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &variable_manager_finalize;

    return (self);
}

variable_manager *variable_manager_new(environment *env)
{
    variable_manager *self =
        (variable_manager *) variable_manager_construct(TYPE_VARIABLE_MANAGER);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) env);

    self->vars = map_new();
    self->env = env;

    return (self);
}

void variable_manager_clear(variable_manager *self)
{
    RETURN_IF_FAIL(self != NULL);

    list_clear(self->vars->list);
}

type *variable_manager_get_type(void)
{
    return (type_register(
        "var.variable_manager",
        sizeof(variable_manager),
        TYPE_OBJECT
    ));
}

void variable_manager_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    variable_manager *self = (variable_manager *) parent;

    object_unref((object *) self->vars);
    object_unref((object *) self->env);

    object_finalize(parent);
}
