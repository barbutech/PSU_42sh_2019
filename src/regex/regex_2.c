/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The regex class.
*/

#include <dirent.h>
#include "regex/regex.h"
#include "regex/pattern.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "io/path.h"
#include "try.h"
#include "type.h"
#include "base.h"

static bool regex_match(string *pattern, string *test, int i1, int i2)
{
    if (pattern->value[i1] == '*' && test->value[i2] == '.' && i2 == 0)
        return (FALSE);

    if (pattern->value[i1] == '*' && test->value[i2] != '\0')
        return (regex_match(pattern, test, i1 + 1, i2) ||
        regex_match(pattern, test, i1, i2 + 1));

    if (pattern->value[i1] == '*' && test->value[i2] == '\0')
        return (regex_match(pattern, test, i1 + 1, i2));

    if (pattern->value[i1] == test->value[i2] && pattern->value[i1] != '\0')
        return (regex_match(pattern, test, i1 + 1, i2 + 1));

    if (pattern->value[i1] == '\0' && test->value[i2] == '\0')
        return (TRUE);

    return (FALSE);
}

static list *regex_get_matched_files(regex *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    list *matches = list_new();

    DIR *dir = opendir(self->path->value->value);
    struct dirent *item;

    if (dir == NULL)
        return (matches);
    while ((item = readdir(dir)) != NULL) {
        string *str = string_new(item->d_name);
        if (regex_match(self->pattern->content, str, 0, 0))
            list_push(matches, (object *) str);
        object_unref((object *) str);
    }

    closedir(dir);
    return (matches);
}

list *regex_research_matches(regex *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    REGEX_RESEARCH;
    return (matches);
}
