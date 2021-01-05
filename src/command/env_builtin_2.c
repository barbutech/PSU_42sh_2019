/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The env_builtin class.
*/

#include "command/env_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "env/environment.h"
#include "util/entry.h"
#include "util/node.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

bool env_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    env_builtin *self = (env_builtin *) parent;

    node *tmp = self->environment->env->list->head;

    while (tmp != NULL) {
        entry *entry_ = (entry *) tmp->value;
        string *key = (string *) entry_->key;
        string *value = (string *) entry_->value;
        console_writeln("%S=%S", key, value);
        tmp = tmp->next;
    }

    return (TRUE);
}

bool env_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("env");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
