/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The setenv_builtin class.
*/

#include "command/setenv_builtin.h"
#include "command/builtin.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "env/environment.h"
#include "io/console.h"
#include "type.h"
#include "base.h"

bool is_alpha(char c)
{
    if ('a' <= c && c <= 'z')
        return (TRUE);

    if ('A' <= c && c <= 'Z')
        return (TRUE);

    return (FALSE);
}

bool is_num(char c)
{
    return ('0' <= c && c <= '9');
}

bool is_alphanum(char c)
{
    return (is_alpha(c) || is_num(c));
}

bool contains_non_alphanum(string *str)
{
    for (int i = 0; i < str->length; i++)
        if (!is_alphanum(str->value[i]))
            return (TRUE);

    return (FALSE);
}
