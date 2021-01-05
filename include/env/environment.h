/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The environment class header.
*/

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "lang/object.h"
#include "lang/string.h"
#include "util/map.h"
#include "type.h"
#include "base.h"

typedef struct environment environment;

struct environment {
    object parent;
    map *env;
    char **array;
};

#define TYPE_ENVIRONMENT (environment_get_type())

#define ENV_DEFAULTS \
if (env[0] == NULL) { \
    char pwd[500]; \
    if (getcwd(pwd, sizeof(pwd)) != NULL) { \
        string *key = string_new("PWD"); \
        string *value = string_new(pwd); \
        environment_set(self, key, value, TRUE); \
        object_unref((object *) key); \
        object_unref((object *) value); \
    } \
    string *key = string_new("PATH"); \
    string *value = string_new( \
        "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \
    ); \
    environment_set(self, key, value, FALSE); \
    object_unref((object *) key); \
    object_unref((object *) value); \
    return; \
}

#define ENV_GEN_ARRAY \
for (int i = 0; node_ != NULL; i++) { \
    entry *entry_ = (entry *) node_->value; \
    string *key = (string *) entry_->key; \
    string *value = (string *) entry_->value; \
    array[i] = malloc(sizeof(char) * (key->length + value->length + 2)); \
    int j = 0; \
    for (int k = 0; k < key->length; j++, k++) \
        array[i][j] = key->value[k]; \
    array[i][j] = '='; \
    j++; \
    for (int k = 0; k < value->length; j++, k++) \
        array[i][j] = value->value[k]; \
    array[i][j] = '\0'; \
    node_ = node_->next; \
}

environment *environment_construct(type *object_type);
environment *environment_new(void);
void environment_set(environment *self, string *name,
    string *value, bool overwrite);
string *environment_get(environment *self, string *name, string *def);
void environment_remove(environment *self, string *name);
bool environment_contains(environment *self, string *name);
void environment_defaults(environment *self, char **env);
void environment_generate_array(environment *self);
string *environment_get_home(environment *self);
string *environment_get_pwd(environment *self);
string *environment_get_user(environment *self);
string *environment_get_path(environment *self);
type *environment_get_type(void);
void environment_finalize(object *parent);

#endif
