/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The which_builtin class header.
*/

#ifndef WHICH_BUILTIN_H
#define WHICH_BUILTIN_H

#include "command/builtin.h"
#include "command/command_manager.h"
#include "env/environment.h"
#include "aliases/alias.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct which_builtin which_builtin;

struct which_builtin {
    builtin parent;
    command_manager *cmd_manager;
    environment *env;
    alias *alias;
    list *args;
};

#define TYPE_WHICH_BUILTIN (which_builtin_get_type())

#define WHICH_BUILTIN_PROCESS_BIN \
string *paths = environment_get_path(self->env); \
string *path_sep = string_new(":"); \
string *file_sep = string_new("/"); \
string **dirs = string_split(paths, path_sep); \
for (int i = 0; dirs != NULL && dirs[i] != NULL; i++) { \
    string *str = string_add(dirs[i], file_sep); \
    string *tmp = string_add(str, cmd); \
    object_unref((object *) str); \
    str = tmp; \
    path *path_ = path_new_from_absolute(tmp); \
    file *file_ = file_new(path_); \
    if (!file_is_executable(file_)) { \
        object_unref((object *) file_); \
        object_unref((object *) path_); \
        object_unref((object *) str); \
        continue; \
    } \
    for (int i = 0; dirs != NULL && dirs[i] != NULL; i++) \
        object_unref((object *) (object *) dirs[i]); \
    console_writeln("%S", path_->value); \
    object_unref((object *) paths); \
    object_unref((object *) path_sep); \
    object_unref((object *) file_sep); \
    object_unref((object *) file_); \
    object_unref((object *) path_); \
    object_unref((object *) str); \
    free(dirs); \
    return (TRUE); \
}

#define WHICH_BUILTIN_PROCESS_LOCAL_BIN \
path *path_ = NULL; \
if (cmd->value[0] == '/') { \
    path_ = path_new_from_absolute(cmd); \
} else { \
    string *pwd = environment_get_pwd(self->env); \
    path *path_pwd = path_new_from_absolute(pwd); \
    path_ = path_new_from_relative(path_pwd, cmd); \
    object_unref((object *) path_pwd); \
    object_unref((object *) pwd); \
} \
file *file_ = file_new(path_); \
if (!file_is_executable(file_)) { \
    object_unref((object *) path_); \
    object_unref((object *) file_); \
    return (FALSE); \
}

which_builtin *which_builtin_construct(type *object_type);
which_builtin *which_builtin_new(
    command_manager *cmd_manager, environment *env, alias *alias
);
bool which_builtin_prepare(builtin *parent, list *arguments);
bool which_builtin_process_bin(which_builtin *self, string *cmd);
bool which_builtin_process_local_bin(which_builtin *self, string *cmd);
bool which_builtin_process_builtin(which_builtin *self, string *cmd);
bool which_builtin_process_alias(which_builtin *self, string *cmd);
bool which_builtin_process(which_builtin *self, string *cmd);
bool which_builtin_execute(builtin *parent);
bool which_builtin_is(builtin *parent, string *name);
type *which_builtin_get_type(void);
void which_builtin_finalize(object *parent);

#endif
