/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The file class.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "io/file.h"
#include "lang/object.h"
#include "io/path.h"
#include "type.h"
#include "base.h"

file *file_construct(type *object_type)
{
    file *self = (file *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &file_finalize;

    return (self);
}

file *file_new(path *path)
{
    file *self = file_construct(TYPE_FILE);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) path);

    self->path = path;

    return (self);
}

bool file_is_regular_file(file *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    struct stat the_stat;

    if (stat(self->path->value->value, &the_stat) == -1)
        return (FALSE);

    return (S_ISREG(the_stat.st_mode));
}

type *file_get_type(void)
{
    return (type_register(
        "io.file",
        sizeof(file),
        TYPE_OBJECT
    ));
}

void file_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    file *self = (file *) parent;

    object_unref((object *) self->path);

    object_finalize(parent);
}
