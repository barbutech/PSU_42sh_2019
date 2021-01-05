/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The variable_manager class header.
*/

#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H

#include "lang/object.h"
#include "lang/string.h"
#include "env/environment.h"
#include "util/map.h"
#include "type.h"
#include "base.h"

typedef struct variable_manager variable_manager;

struct variable_manager {
    object parent;
    map *vars;
    environment *env;
};

#define TYPE_VARIABLE_MANAGER (variable_manager_get_type())

variable_manager *variable_manager_construct(type *object_type);
variable_manager *variable_manager_new(environment *env);
void variable_manager_set(variable_manager *self, string *name, string *value);
string *variable_manager_get(variable_manager *self, string *name);
void variable_manager_remove(variable_manager *self, string *name);
bool variable_manager_contains(variable_manager *self, string *name);
bool variable_manager_contains_in_env(variable_manager *self, string *name);
void variable_manager_clear(variable_manager *self);
type *variable_manager_get_type(void);
void variable_manager_finalize(object *self);

#endif
