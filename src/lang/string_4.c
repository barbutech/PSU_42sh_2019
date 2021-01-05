/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The string class.
*/

#include <stdlib.h>
#include "lang/string.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"


string *string_add(string *self, string *another)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    int length = self->length + another->length;
    char *value = malloc(sizeof(char) * (length + 1));

    int i = 0;
    for (; i < self->length; i++)
        value[i] = self->value[i];
    for (int j = 0; j < another->length; i++, j++)
        value[i] = another->value[j];
    value[i] = '\0';

    string *str = string_new(value);

    free(value);
    return (str);
}

bool string_has_prefix(string *self, string *another)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    if (self->length < another->length)
        return (FALSE);

    for (int i = 0; i < another->length; i++) {
        if (self->value[i] == another->value[i])
            continue;
        return (FALSE);
    }

    return (TRUE);
}

string *string_stringify(object *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);
    string *self = (string *) parent;

    object_ref((object *) self);
    return (self);
}

bool string_equals(object *parent, object *another)
{
    RETURN_VAL_IF_FAIL(parent != NULL, FALSE);
    string *self = (string *) parent;

    if (!instance_of(another, parent->object_type)) {
        return (FALSE);
    }

    string *str = (string *) another;

    if (self->length != str->length)
        return (FALSE);

    for (int i = 0; i < self->length; i++) {
        if (self->value[i] == str->value[i])
            continue;
        return (FALSE);
    }

    return (TRUE);
}

char *string_clone_to_primitive(string *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    char *content = malloc(sizeof(char) * (self->length + 1));

    for (int i = 0; i < self->length; i++)
        content[i] = self->value[i];

    content[self->length] = '\0';

    return (content);
}
