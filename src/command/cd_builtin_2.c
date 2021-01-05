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

bool cd_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    cd_builtin *self = (cd_builtin *) parent;

    if (arguments->size > 1) {
        console_errln("cd: Too many arguments.");
        return (FALSE);
    }
    if (arguments->size == 0) {
        object_unref((object *) self->path);
        self->path = NULL;
        return (TRUE);
    }
    object_unref((object *) self->path);
    self->path = (string *) arguments->head->value;
    object_ref((object *) self->path);

    return (TRUE);
}

static path *cd_builtin_get_absolute_path(cd_builtin *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *str = string_clone(self->path);
    string *home = environment_get_home(self->environment);
    if (home != NULL && string_has_prefix(str, self->tilde)) {
        string *tmp = string_add(home, self->separator);
        string *tmp2 = string_substring(str, 1, str->length);
        string *tmp3 = string_add(tmp, tmp2);
        object_unref((object *) str);
        str = tmp3;
        object_unref((object *) tmp);
        object_unref((object *) tmp2);
    }
    path *path_ = path_new_from_absolute(str);
    object_unref((object *) str);
    object_unref((object *) home);
    return (path_);
}

static path *cd_builtin_get_relative_path(cd_builtin *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *pwd = environment_get_pwd(self->environment);
    path *abs = path_new_from_absolute(pwd);
    path *path_ = path_new_from_relative(abs, self->path);

    object_unref((object *) pwd);
    object_unref((object *) abs);
    return (path_);
}

static path *cd_builtin_get_old_path(cd_builtin *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *str = environment_get(self->environment, self->old_pwd_key, NULL);

    if (str == NULL)
        return (NULL);

    path *path_ = path_new_from_absolute(str);

    object_unref((object *) str);
    return (path_);
}

bool cd_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    cd_builtin *self = (cd_builtin *) parent;

    path *path_;
    CD_BUILTIN_EXEC;
    string *pwd = environment_get_pwd(self->environment);
    environment_set(self->environment, self->old_pwd_key, pwd, TRUE);
    environment_set(self->environment, self->pwd_key, path_->value, TRUE);
    object_unref((object *) pwd);
    object_unref((object *) path_);
    object_unref((object *) file_);

    return (TRUE);
}
