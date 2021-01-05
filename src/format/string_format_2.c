/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The string_format class.
*/

#include <stdarg.h>
#include "format/string_format.h"
#include "format/format.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

string *string_format_process(format *parent, va_list args)
{
    RETURN_VAL_IF_FAIL(parent != NULL, NULL);

    string *str = va_arg(args, string *);

    object_ref((object *) str);
    return (str);
}

char string_format_get_flag(format *parent)
{
    RETURN_VAL_IF_FAIL(parent != NULL, '\0');

    return ('S');
}
