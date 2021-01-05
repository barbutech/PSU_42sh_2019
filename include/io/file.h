/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The file class header.
*/

#ifndef FILE_H
#define FILE_H

#include "lang/object.h"
#include "io/path.h"
#include "type.h"
#include "base.h"

typedef struct file file;

struct file {
    object parent;
    path *path;
};

#define TYPE_FILE (file_get_type())

file *file_construct(type *object_type);
file *file_new(path *path);
bool file_is_accessible(file *self, int mode);
bool file_exists(file *self);
bool file_is_readable(file *self);
bool file_is_writable(file *self);
bool file_is_executable(file *self);
bool file_is_regular_file(file *self);
type *file_get_type(void);
void file_finalize(object *parent);

#endif
