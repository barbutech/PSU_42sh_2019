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

bool file_is_accessible(file *self, int mode)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (access(self->path->value->value, mode) == 0);
}

bool file_exists(file *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (file_is_accessible(self, F_OK));
}

bool file_is_readable(file *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (file_is_accessible(self, R_OK));
}

bool file_is_writable(file *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (file_is_accessible(self, W_OK));
}

bool file_is_executable(file *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    return (file_is_accessible(self, X_OK));
}
