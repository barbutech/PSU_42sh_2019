/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The setenv_builtin class.
*/

#include "command/setenv_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

setenv_builtin *setenv_builtin_construct(type *object_type)
{
    setenv_builtin *self = (setenv_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &setenv_builtin_finalize;

    return (self);
}

setenv_builtin *setenv_builtin_new(environment *environment)
{
    setenv_builtin *self = setenv_builtin_construct(TYPE_SETENV_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->environment = environment;

    self->key = NULL;
    self->value = NULL;

    ((builtin *) self)->prepare = &setenv_builtin_prepare;
    ((builtin *) self)->execute = &setenv_builtin_execute;
    ((builtin *) self)->is = &setenv_builtin_is;

    return (self);
}

type *setenv_builtin_get_type(void)
{
    return (type_register(
        "builtin.setenv_builtin",
        sizeof(setenv_builtin),
        TYPE_BUILTIN
    ));
}

void setenv_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    setenv_builtin *self = (setenv_builtin *) parent;

    object_unref((object *) self->key);
    object_unref((object *) self->value);

    object_finalize(parent);
}
