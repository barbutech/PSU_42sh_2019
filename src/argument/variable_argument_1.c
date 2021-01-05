/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The variable_argument class.
*/

#include "argument/variable_argument.h"
#include "argument/argument.h"
#include "var/variable_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

variable_argument *variable_argument_construct(type *object_type)
{
    variable_argument *self = (variable_argument *)
        argument_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &variable_argument_finalize;

    return (self);
}

variable_argument *variable_argument_new(string *var_name,
    variable_manager *var_manager)
{
    variable_argument *self =
        variable_argument_construct(TYPE_VARIABLE_ARGUMENT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) var_name);
    object_ref((object *) var_manager);

    self->var_name = var_name;
    self->var_manager = var_manager;

    ((argument *) self)->get_content = &variable_argument_get_content;
    ((argument *) self)->is_accessible = &variable_argument_is_accessible;

    return (self);
}

type *variable_argument_get_type(void)
{
    return (type_register(
        "argument.variable_argument",
        sizeof(variable_argument),
        TYPE_ARGUMENT
    ));
}

void variable_argument_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    variable_argument *self = (variable_argument *) parent;

    object_unref((object *) self->var_name);
    object_unref((object *) self->var_manager);

    argument_finalize(parent);
}
