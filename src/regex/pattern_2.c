/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The pattern class.
*/

#include "regex/pattern.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

list *pattern_extract_subpatterns(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (pattern_contains_hierarchical_subpatterns(self))
        return (pattern_extract_hierarchical_subpatterns(self));

    if (pattern_contains_choice_subpatterns(self))
        return (pattern_extract_choice_subpatterns(self));

    return (NULL);
}

list *pattern_extract_hierarchical_subpatterns(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    list *subpatterns = list_new();
    int start = 0;
    int end = 0;
    int parentheses_counter = 0;
    PATTERN_EXTRACT_HIERARCHICAL;
    string *substr = string_substring(self->content, start, end);
    pattern *subpattern = pattern_new(substr);
    list_push(subpatterns, (object *) subpattern);
    object_unref((object *) subpattern);
    object_unref((object *) substr);

    return (subpatterns);
}

list *pattern_extract_choice_subpatterns(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    list *subpatterns = list_new();
    list *choices = list_new();
    int start = 0;
    int end = 0;
    int parentheses_counter = 0;
    bool is_choice = FALSE;
    string *prefix = NULL;
    string *choice = NULL;
    string *suffix = NULL;
    PATTERN_EXTRACT_CHOICE;
    object_unref((object *) choices);
    object_unref((object *) prefix);
    object_unref((object *) choice);
    object_unref((object *) suffix);
    return (subpatterns);
}
