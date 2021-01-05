/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** alias_builtin.c
*/

#include "command/builtin.h"
#include "command/unalias_builtin.h"
#include "aliases/alias.h"
#include "util/entry.h"

bool unalias_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    unalias_builtin *self = (unalias_builtin *) parent;

    if (arguments->size < 1) {
        console_errln("unalias: not enough arguments");
        return (FALSE);
    }

    object_unref((object *)self->arguments);
    self->arguments = arguments;
    object_ref((object *) self->arguments);

    return (TRUE);
}

bool unalias_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    unalias_builtin *self = (unalias_builtin *) parent;
    node *tmp = self->arguments->head;
        while (tmp) {
            string *key = (string *) tmp->value;

        alias_case_unalias(self->alias, key);
        tmp = tmp->next;
        }
    return (TRUE);
}

bool unalias_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("unalias");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
