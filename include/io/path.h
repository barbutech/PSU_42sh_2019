/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The path class header.
*/

#ifndef PATH_H
#define PATH_H

#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct path path;

struct path {
    object parent;
    string *value;
};

#define TYPE_PATH (path_get_type())

#define PATH_NEW_REL \
stack *stack_ = stack_new(); \
string **dirs = path_extract_directories(absolute); \
for (int i = 0; dirs[i] != NULL; i++) { \
    stack_push(stack_, (object *) dirs[i]); \
    object_unref((object *) dirs[i]); \
} \
free(dirs); \
string *separator = string_new("/"); \
string *current = string_new("."); \
string *back = string_new(".."); \
dirs = string_split(relative, separator); \
for (int i = 0; dirs[i] != NULL; i++) { \
    if (object_equals((object *) dirs[i], (object *) back)) { \
        object_unref(stack_pop(stack_)); \
    } else if (!object_equals((object *) dirs[i], (object *) current)) { \
        stack_push(stack_, (object *) dirs[i]); \
    } \
    object_unref((object *) dirs[i]); \
} \
free(dirs); \
self->value = list_join(stack_->list, separator, TRUE); \
object_unref((object *) separator); \
object_unref((object *) current); \
object_unref((object *) back); \
object_unref((object *) stack_);

#define PATH_CREATE_REL_PATH \
string **dirs_1 = path_extract_directories(self); \
string **dirs_2 = path_extract_directories(another); \
int i = 0; \
for (; dirs_1[i] != NULL; i++) { \
    if (dirs_2[i] == NULL) \
        break; \
    if (!string_equals((object *) dirs_1[i], (object *) dirs_2[i])) \
        break; \
} \
if (dirs_1[i] == NULL) { \
    for (int j = i; dirs_2[j] != NULL; j++) \
        list_push(relative_path, (object *) dirs_2[j]); \
} else { \
    string *prev = string_new(".."); \
    for (int j = i; dirs_1[j] != NULL; j++) { \
        list_push(relative_path, (object *) prev); \
    } \
    for (int j = i; dirs_2[j] != NULL; j++) { \
        list_push(relative_path, (object *) dirs_2[j]); \
    } \
    object_unref((object *) prev); \
} \
for (int j = 0; dirs_1[j] != NULL; j++) \
    object_unref((object *) dirs_1[j]); \
for (int j = 0; dirs_2[j] != NULL; j++) \
    object_unref((object *) dirs_2[j]); \
free(dirs_1); \
free(dirs_2); \
string *glue = string_new("/"); \
string *relative_path_str = list_join(relative_path, glue, FALSE); \
object_unref((object *) relative_path); \
object_unref((object *) glue); \
if (relative_path_str->length == 0) { \
    object_unref((object *) relative_path_str); \
    relative_path_str = string_new("."); \
}

path *path_construct(type *object_type);
path *path_new_from_root(void);
path *path_new_from_absolute(string *str);
path *path_new_from_relative(path *absolute, string *relative);
string **path_extract_directories(path *self);
string *path_create_relative_path(path *self, path *another);
type *path_get_type(void);
void path_finalize(object *parent);

#endif
