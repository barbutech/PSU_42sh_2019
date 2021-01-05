/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The unsetenv_builtin class.
*/

#include "command/unsetenv_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "util/node.h"
#include "env/environment.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

unsetenv_builtin *unsetenv_builtin_construct(type *object_type)
{
    unsetenv_builtin *self = (unsetenv_builtin *)
        builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &unsetenv_builtin_finalize;

    return (self);
}

unsetenv_builtin *unsetenv_builtin_new(environment *environment)
{
    unsetenv_builtin *self = unsetenv_builtin_construct(TYPE_UNSETENV_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->environment = environment;

    self->arguments = NULL;

    ((builtin *) self)->prepare = &unsetenv_builtin_prepare;
    ((builtin *) self)->execute = &unsetenv_builtin_execute;
    ((builtin *) self)->is = &unsetenv_builtin_is;

    return (self);
}

type *unsetenv_builtin_get_type(void)
{
    return (type_register(
        "builtin.unsetenv_builtin",
        sizeof(unsetenv_builtin),
        TYPE_BUILTIN
    ));
}

void unsetenv_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    unsetenv_builtin *self = (unsetenv_builtin *) parent;

    object_unref((object *) self->arguments);

    object_finalize(parent);
}
