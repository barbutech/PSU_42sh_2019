/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The repeat_builtin class.
*/

#include "command/repeat_builtin.h"
#include "command/builtin.h"
#include "command/command_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "io/console.h"
#include "argument/argument.h"
#include "argument/plain_argument.h"
#include "type.h"
#include "base.h"

static int string_to_int(string *str)
{
    int n = 0;
    int i = 0;

    if (str->value[i] == '+' || str->value[i] == '-')
        i++;
    for (; i < str->length; i++) {
        if ('0' > str->value[i] || str->value[i] > '9')
            return (-1);
        n = (n * 10) + (str->value[i] - '0');
    }

    return (n);
}

bool repeat_builtin_prepare(builtin *parent, list *arguments)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    repeat_builtin *self = (repeat_builtin *) parent;

    if (arguments->size < 2) {
        console_errln("repeat: Too few arguments.");
        return (FALSE);
    }
    REPEAT_BUILTIN_PREPARE;
    return (TRUE);
}

bool repeat_builtin_execute(builtin *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    repeat_builtin *self = (repeat_builtin *) parent;

    for (int i = 0; i < self->n; i++) {
        command_manager_call(
            self->cmd_manager, self->name, self->args, REDIRECT_STANDARD
        );
    }

    return (TRUE);
}

bool repeat_builtin_is(builtin *parent, string *name)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);

    string *name_ = string_new("repeat");
    bool result = string_equals((object *) name_, (object *) name);

    object_unref((object *) name_);
    return (result);
}
