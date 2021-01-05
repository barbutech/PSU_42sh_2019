/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The where_builtin class.
*/

#include <stdlib.h>
#include "command/where_builtin.h"
#include "command/builtin.h"
#include "command/command_manager.h"
#include "env/environment.h"
#include "aliases/alias.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "util/node.h"
#include "io/file.h"
#include "io/path.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

bool where_builtin_process_bin(where_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);
    bool success = FALSE;

    string *paths = environment_get_path(self->env);
    string *path_sep = string_new(":");
    string *file_sep = string_new("/");
    string **dirs = string_split(paths, path_sep);
    WHERE_BUILTIN_PROCESS_BIN;
    object_unref((object *) paths);
    object_unref((object *) path_sep);
    object_unref((object *) file_sep);
    free(dirs);

    return (success);
}

bool where_builtin_process_local_bin(where_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    path *path_ = NULL;
    WHERE_BUILTIN_PROCESS_LOCAL_BIN;
    object_unref((object *) path_);
    object_unref((object *) file_);

    return (TRUE);
}

bool where_builtin_process_builtin(where_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    node *tmp = self->cmd_manager->builtins->head;
    while (tmp != NULL) {
        builtin *builtin_ = (builtin *) tmp->value;
        if (!builtin_is(builtin_, cmd)) {
            tmp = tmp->next;
            continue;
        }
        console_writeln("%S: shell built-in command.", cmd);
        return (TRUE);
    }
    return (FALSE);
}

bool where_builtin_process_alias(where_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (!alias_contains(self->alias, cmd))
        return (FALSE);

    string *aliased = alias_get(self->alias, cmd);

    console_writeln("%S is aliased to %S", cmd, aliased);

    object_unref((object *) aliased);
    return (TRUE);
}

bool where_builtin_process(where_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);
    bool success = FALSE;

    if (where_builtin_process_alias(self, cmd))
        success = TRUE;

    if (where_builtin_process_builtin(self, cmd))
        success = TRUE;

    if (where_builtin_process_bin(self, cmd))
        success = TRUE;

    if (where_builtin_process_local_bin(self, cmd))
        success = TRUE;

    return (success);
}
