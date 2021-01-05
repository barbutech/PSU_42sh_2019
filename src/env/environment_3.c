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

void environment_defaults(environment *self, char **env)
{
    RETURN_IF_FAIL(self != NULL);

    ENV_DEFAULTS;
    string *separator = string_new("=");
    for (int i = 0; env[i] != NULL; i++) {
        string *line = string_new(env[i]);
        int pivot = string_index_of(line, separator);
        string *key = string_substring(line, 0, pivot);
        string *value = string_substring(line, pivot + 1, line->length);
        environment_set(self, key, value, FALSE);
        object_unref((object *) key);
        object_unref((object *) value);
        object_unref((object *) line);
    }
    object_unref((object *) separator);
}

void environment_generate_array(environment *self)
{
    RETURN_IF_FAIL(self != NULL);

    char **array = malloc(sizeof(char *) * (self->env->list->size + 1));
    string *sep = string_new("=");
    node *node_ = self->env->list->head;
    ENV_GEN_ARRAY;
    array[self->env->list->size] = NULL;
    for (int i = 0; self->array != NULL && self->array[i] != NULL; i++)
        free(self->array[i]);
    free(self->array);
    self->array = array;
    object_unref((object *) sep);
}
