/*
** EPITECH PROJECT, 2019
** test
** File description:
** set_var_builtin.c
*/

#include "io/console.h"
#include "base.h"
#include "type.h"
#include "command/set_var_builtin.h"
#include "var/variable_manager.h"

setvar_builtin *setvar_builtin_construct(type *object_type)
{
    setvar_builtin *self = (setvar_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &setvar_builtin_finalize;

    return (self);
}

setvar_builtin *setvar_builtin_new(variable_manager *var_man)
{
    setvar_builtin *self = setvar_builtin_construct(TYPE_SETVAR_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->variable_manager = var_man;

    self->key = NULL;
    self->value = NULL;

    ((builtin *) self)->prepare = &setvar_builtin_prepare;
    ((builtin *) self)->execute = &setvar_builtin_execute;
    ((builtin *) self)->is = &setvar_builtin_is;

    return (self);
}

type *setvar_builtin_get_type(void)
{
    return (type_register(
        "builtin.setvar_builtin",
        sizeof(setvar_builtin),
        TYPE_BUILTIN
    ));
}

void setvar_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    setvar_builtin *self = (setvar_builtin *) parent;

    object_unref((object *) self->key);
    object_unref((object *) self->value);

    object_finalize(parent);
}
