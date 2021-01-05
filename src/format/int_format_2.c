/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The int_format class.
*/

#include <stdarg.h>
#include "format/int_format.h"
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

string *int_format_process(format *parent, va_list args)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);

    int n = va_arg(args, int);

    return (string_new_from_int(n));
}

char int_format_get_flag(format *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, '\0');

    return ('i');
}
