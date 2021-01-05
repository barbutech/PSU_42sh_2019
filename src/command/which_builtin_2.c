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

bool which_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    which_builtin *self = (which_builtin *) parent;

    if (arguments->size < 1) {
        console_errln("which: Too few arguments.");
        return (FALSE);
    }

    object_unref((object *) self->args);
    self->args = arguments;
    object_ref((object *) self->args);

    return (TRUE);
}

bool which_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    which_builtin *self = (which_builtin *) parent;

    node *tmp = self->args->head;
    bool success = TRUE;

    while (tmp != NULL) {
        if (!which_builtin_process(self, (string *) tmp->value))
            success = FALSE;
        tmp = tmp->next;
    }

    return (success);
}

bool which_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("which");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
