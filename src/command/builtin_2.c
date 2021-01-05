/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The builtin abstract class.
*/

#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

bool builtin_prepare(builtin *self, list *arguments)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (self->prepare == NULL)
        return (TRUE);

    return (self->prepare(self, arguments));
}

bool builtin_execute(builtin *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (self->execute == NULL)
        return (FALSE);

    return (self->execute(self));
}

void builtin_dispose(builtin *self)
{
    RETURN_IF_FAIL(self != NULL);

    if (self->dispose == NULL)
        return;

    self->dispose(self);
}

bool builtin_is(builtin *self, string *name)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (self->is == NULL)
        return (FALSE);

    return (self->is(self, name));
}
