/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The type utility.
*/

#include <stdlib.h>
#include "lang/object.h"
#include "type.h"
#include "base.h"

static bool str_equals(char *str1, char *str2)
{
    int i = 0;
    for (; str1[i] != '\0' || str2[i] != '\0'; i++) {
        if (str1[i] != str2[i])
            return (FALSE);
    }

    return (str1[i] == str2[i] && str1[i] == '\0');
}

bool instance_of(object *self, type *object_type)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);
    RETURN_VAL_IF_FAIL(object_type != NULL, FALSE);

    bool result = FALSE;

    char *name = object_type->name;
    type *self_type = self->object_type;

    while (self_type != NULL) {

        if (!result)
            result = str_equals(self_type->name, name);

        self_type = self_type->parent;
    }

    return (result);
}
