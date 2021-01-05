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

bool pattern_contains_subpatterns(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);
    bool hierarchical = pattern_contains_hierarchical_subpatterns(self);
    bool choice = pattern_contains_choice_subpatterns(self);
    return (hierarchical || choice);
}

bool pattern_contains_hierarchical_subpatterns(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    int parentheses_counter = 0;

    for (int i = 0; i < self->content->length; i++) {
        char c = self->content->value[i];
        if (c == '/' && parentheses_counter == 0)
            return (TRUE);
        parentheses_counter += (c == '(');
        parentheses_counter -= (c == ')');
    }
    return (FALSE);
}

bool pattern_contains_choice_subpatterns(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    for (int i = 0; i < self->content->length; i++) {
        char c = self->content->value[i];
        if (c == '(')
            return (TRUE);
    }

    return (FALSE);
}

bool pattern_is_correct(pattern *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    int parentheses_counter = 0;

    for (int i = 0; i < self->content->length; i++) {
        char c = self->content->value[i];
        if (parentheses_counter < 0)
            return (FALSE);
        parentheses_counter += (c == '(');
        parentheses_counter -= (c == ')');
    }
    return (parentheses_counter == 0);
}
