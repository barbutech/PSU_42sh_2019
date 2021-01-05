/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The environment class.
*/

#include <stdlib.h>
#include <unistd.h>
#include "env/environment.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/map.h"
#include "util/node.h"
#include "util/entry.h"
#include "type.h"
#include "base.h"

string *environment_get_home(environment *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *key = string_new("HOME");
    string *value = environment_get(self, key, NULL);

    object_unref((object *) key);
    return (value);

}

string *environment_get_pwd(environment *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *key = string_new("PWD");
    string *def = string_new("/");

    string *value = environment_get(self, key, def);

    object_unref((object *) key);
    object_unref((object *) def);
    return (value);
}

string *environment_get_user(environment *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *key = string_new("USER");
    string *def = string_new("user");

    string *value = environment_get(self, key, def);

    object_unref((object *) key);
    object_unref((object *) def);
    return (value);
}

string *environment_get_path(environment *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    string *key = string_new("PATH");
    string *def = string_new("");

    string *value = environment_get(self, key, def);

    object_unref((object *) key);
    object_unref((object *) def);
    return (value);
}
