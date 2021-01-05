/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The map class header.
*/

#ifndef MAP_H
#define MAP_H

#include "lang/object.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct map map;

struct map {
    object parent;
    list *list;
};

#define TYPE_MAP (map_get_type())

map *map_construct(type *object_type);
map *map_new(void);
void map_set(map *self, object *key, object *value);
void map_change(map *self, object *key, object *new_value);
bool map_contains(map *self, object *key);
object *map_get(map *self, object *key);
void map_remove(map *self, object *key);
int map_get_index_by_key(map *self, object *key);
type *map_get_type(void);
void map_finalize(object *parent);

#endif
