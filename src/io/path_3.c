/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The path class.
*/

#include <stdlib.h>
#include "io/path.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/stack.h"
#include "type.h"
#include "base.h"

string **path_extract_directories(path *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *separator = string_new("/");
    string **dirs = string_split(self->value, separator);

    object_unref((object *) separator);
    return (dirs);
}

string *path_create_relative_path(path *self, path *another)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    list *relative_path = list_new();

    PATH_CREATE_REL_PATH;
    return (relative_path_str);
}
