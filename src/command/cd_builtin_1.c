/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The cd_builtin class.
*/

#include <unistd.h>
#include "command/cd_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "io/console.h"
#include "io/path.h"
#include "io/file.h"
#include "type.h"
#include "base.h"

cd_builtin *cd_builtin_construct(type *object_type)
{
    cd_builtin *self = (cd_builtin *) builtin_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &cd_builtin_finalize;

    return (self);
}

cd_builtin *cd_builtin_new(environment *environment)
{
    cd_builtin *self = cd_builtin_construct(TYPE_CD_BUILTIN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->environment = environment;
    self->path = NULL;

    self->pwd_key = string_new("PWD");
    self->old_pwd_key = string_new("OLD_PWD");
    self->hyphen = string_new("-");
    self->tilde = string_new("~");
    self->separator = string_new("/");

    ((builtin *) self)->prepare = &cd_builtin_prepare;
    ((builtin *) self)->execute = &cd_builtin_execute;
    ((builtin *) self)->is = &cd_builtin_is;

    return (self);
}

bool cd_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("cd");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}

type *cd_builtin_get_type(void)
{
    return (type_register(
        "builtin.cd_builtin",
        sizeof(cd_builtin),
        TYPE_BUILTIN
    ));
}

void cd_builtin_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    cd_builtin *self = (cd_builtin *) parent;

    object_unref((object *) self->path);

    object_unref((object *) self->pwd_key);
    object_unref((object *) self->old_pwd_key);
    object_unref((object *) self->hyphen);
    object_unref((object *) self->tilde);
    object_unref((object *) self->separator);

    object_finalize(parent);
}
