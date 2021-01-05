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

string *variable_argument_get_content(argument *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);
    variable_argument *self = (variable_argument *) parent;

    return (variable_manager_get(self->var_manager, self->var_name));
}

bool variable_argument_is_accessible(argument *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    variable_argument *self = (variable_argument *) parent;

    string *content = variable_manager_get(self->var_manager, self->var_name);
    bool is_accessible = content != NULL;

    if (!is_accessible)
        console_errln("%S: Undefined variable.", self->var_name);

    object_unref((object *) content);

    return (is_accessible);
}
