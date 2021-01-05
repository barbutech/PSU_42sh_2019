/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The where_builtin class header.
*/

#ifndef WHERE_BUILTIN_H
#define WHERE_BUILTIN_H

#include "command/builtin.h"
#include "command/command_manager.h"
#include "env/environment.h"
#include "aliases/alias.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct where_builtin where_builtin;

struct where_builtin {
    builtin parent;
    command_manager *cmd_manager;
    environment *env;
    alias *alias;
    list *args;
};

#define TYPE_WHERE_BUILTIN (where_builtin_get_type())

#define WHERE_BUILTIN_PROCESS_BIN \
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
    console_writeln("%S", path_->value); \
    object_unref((object *) file_); \
    object_unref((object *) path_); \
    object_unref((object *) str); \
    success = TRUE; \
} \
for (int i = 0; dirs != NULL && dirs[i] != NULL; i++) \
    object_unref((object *) (object *) dirs[i]);

#define WHERE_BUILTIN_PROCESS_LOCAL_BIN \
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
} \
console_writeln("%S", cmd);

where_builtin *where_builtin_construct(type *object_type);
where_builtin *where_builtin_new(
    command_manager *cmd_manager, environment *env, alias *alias
);
bool where_builtin_prepare(builtin *parent, list *arguments);
bool where_builtin_process_bin(where_builtin *self, string *cmd);
bool where_builtin_process_local_bin(where_builtin *self, string *cmd);
bool where_builtin_process_builtin(where_builtin *self, string *cmd);
bool where_builtin_process_alias(where_builtin *self, string *cmd);
bool where_builtin_process(where_builtin *self, string *cmd);
bool where_builtin_execute(builtin *parent);
bool where_builtin_is(builtin *parent, string *name);
type *where_builtin_get_type(void);
void where_builtin_finalize(object *parent);

#endif
