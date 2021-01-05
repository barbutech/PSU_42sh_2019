/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The chararray_format class.
*/

#include <stdarg.h>
#include "format/chararray_format.h"
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

string *chararray_format_process(format *parent, va_list args)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);

    char *str = va_arg(args, char *);

    return (string_new(str));
}

char chararray_format_get_flag(format *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, '\0');

    return ('s');
}
