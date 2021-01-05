/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The which_builtin class.
*/

#include <stdlib.h>
#include "command/which_builtin.h"
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

bool which_builtin_process_bin(which_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    WHICH_BUILTIN_PROCESS_BIN;
    for (int i = 0; dirs != NULL && dirs[i] != NULL; i++)
        object_unref((object *) (object *) dirs[i]);
    object_unref((object *) paths);
    object_unref((object *) path_sep);
    object_unref((object *) file_sep);
    free(dirs);

    return (FALSE);
}

bool which_builtin_process_local_bin(which_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    WHICH_BUILTIN_PROCESS_LOCAL_BIN;
    console_writeln("%S", cmd);
    object_unref((object *) path_);
    object_unref((object *) file_);

    return (TRUE);
}

bool which_builtin_process_builtin(which_builtin *self, string *cmd)
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

bool which_builtin_process_alias(which_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (!alias_contains(self->alias, cmd))
        return (FALSE);

    string *aliased = alias_get(self->alias, cmd);

    console_writeln("%S: 	 aliased to %S", cmd, aliased);

    object_unref((object *) aliased);
    return (TRUE);
}

bool which_builtin_process(which_builtin *self, string *cmd)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (which_builtin_process_alias(self, cmd))
        return (TRUE);

    if (which_builtin_process_builtin(self, cmd))
        return (TRUE);

    if (which_builtin_process_bin(self, cmd))
        return (TRUE);

    if (which_builtin_process_local_bin(self, cmd))
        return (TRUE);

    console_errln("%S: Command not found.", cmd);
    return (FALSE);
}
