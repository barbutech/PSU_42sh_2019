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

path *path_new_from_root(void)
{
    path *self = path_construct(TYPE_PATH);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->value = string_new("/");

    return (self);
}

path *path_new_from_absolute(string *str)
{
    path *root = path_new_from_root();
    path *path_ = path_new_from_relative(root, str);

    object_unref((object *) root);
    return (path_);
}

path *path_new_from_relative(path *absolute, string *relative)
{
    path *self = path_construct(TYPE_PATH);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    PATH_NEW_REL;
    return (self);
}
