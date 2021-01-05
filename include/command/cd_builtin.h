/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The cd_builtin class header.
*/

#ifndef CD_BUILTIN_H
#define CD_BUILTIN_H

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "type.h"
#include "base.h"

typedef struct cd_builtin cd_builtin;

struct cd_builtin {
    builtin parent;
    environment *environment;
    string *path;
    string *pwd_key;
    string *old_pwd_key;
    string *hyphen;
    string *tilde;
    string *separator;
};

#define TYPE_CD_BUILTIN (cd_builtin_get_type())

#define CD_BUILTIN_EXEC \
if (self->path == NULL) { \
    string *home = environment_get_home(self->environment); \
    if (home == NULL) return (FALSE); \
    path_ = path_new_from_absolute(home); \
    object_unref((object *) home); \
} else if ( \
    string_has_prefix(self->path, self->tilde) || \
    string_has_prefix(self->path, self->separator) \
) \
    path_ = cd_builtin_get_absolute_path(self); \
else if (object_equals((object *) self->path, (object *) self->hyphen)) \
    path_ = cd_builtin_get_old_path(self); \
else \
    path_ = cd_builtin_get_relative_path(self); \
if (path_ == NULL) { \
    console_errln(": No such file or folder."); \
    return (FALSE); \
} \
file *file_ = file_new(path_); \
if (!file_exists(file_)) { \
    console_errln("%S: No such file or folder.", \
    self->path != NULL ? self->path : path_->value); \
    object_unref((object *) path_); \
    object_unref((object *) file_); \
    return (FALSE); \
} \
if (file_is_regular_file(file_)) { \
    console_errln("%S: Not a directory.", \
    self->path != NULL ? self->path : path_->value); \
    object_unref((object *) path_); \
    object_unref((object *) file_); \
    return (FALSE); \
} \
if (chdir(path_->value->value) == -1) { \
    console_errln("%S: Unable to access.", \
    self->path != NULL ? self->path : path_->value); \
    object_unref((object *) path_); \
    object_unref((object *) file_); \
    return (FALSE); \
}

cd_builtin *cd_builtin_construct(type *object_type);
cd_builtin *cd_builtin_new(environment *environment);
bool cd_builtin_prepare(builtin *parent, list *arguments);
bool cd_builtin_execute(builtin *parent);
bool cd_builtin_is(builtin *parent, string *name);
type *cd_builtin_get_type(void);
void cd_builtin_finalize(object *parent);

#endif
