/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The pattern class header.
*/

#ifndef PATTERN_H
#define PATTERN_H

#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct pattern pattern;

struct pattern {
    object parent;
    string *content;
};

#define TYPE_PATTERN (pattern_get_type())

#define PATTERN_EXTRACT_HIERARCHICAL \
for (int i = 0; i < self->content->length; i++, end++) { \
    char c = self->content->value[i]; \
    if (c == '/' && parentheses_counter == 0) { \
        string *substr = string_substring(self->content, start, end); \
        pattern *subpattern = pattern_new(substr); \
        list_push(subpatterns, (object *) subpattern); \
        start = end + 1; \
        object_unref((object *) subpattern); \
        object_unref((object *) substr); \
    } \
    parentheses_counter += (c == '('); \
    parentheses_counter -= (c == ')'); \
}

#define PATTERN_EXTRACT_CHOICE \
for (int i = 0; i < self->content->length; i++, end++) { \
    char c = self->content->value[i]; \
    if (c == '(' && !is_choice) { \
        prefix = string_substring(self->content, start, end); \
        start = end + 1; \
        is_choice = TRUE; \
    } \
    parentheses_counter += (c == '('); \
    parentheses_counter -= (c == ')'); \
    if (c == '|' && is_choice && parentheses_counter == 1) { \
        string *substr = string_substring(self->content, start, end); \
        list_push(choices, (object *) substr); \
        start = end + 1; \
        object_unref((object *) substr); \
    } \
    if (c == ')' && is_choice && parentheses_counter == 0) { \
        string *substr = string_substring(self->content, start, end); \
        list_push(choices, (object *) substr); \
        start = end + 1; \
        object_unref((object *) substr); \
        suffix = string_substring(self->content, start, self->content->length);\
        break; \
    } \
} \
node *tmp = choices->head; \
while (tmp != NULL) { \
    object_ref(tmp->value); \
    string *str = (string *) tmp->value; \
    string *tmp2 = NULL; \
    tmp2 = string_add(prefix, str); \
    object_unref((object *) str); \
    object_ref((object *) tmp2); \
    str = tmp2; \
    object_unref((object *) tmp2); \
    tmp2 = string_add(str, suffix); \
    object_unref((object *) str); \
    object_ref((object *) tmp2); \
    str = tmp2; \
    pattern *pattern_ = pattern_new(str); \
    list_push(subpatterns, (object *) pattern_); \
    object_unref((object *) pattern_); \
    object_unref((object *) str); \
    object_unref((object *) tmp2); \
    tmp = tmp->next; \
}

pattern *pattern_construct(type *object_type);
pattern *pattern_new(string *content);
list *pattern_extract_subpatterns(pattern *self);
list *pattern_extract_hierarchical_subpatterns(pattern *self);
list *pattern_extract_choice_subpatterns(pattern *self);
bool pattern_contains_subpatterns(pattern *self);
bool pattern_contains_hierarchical_subpatterns(pattern *self);
bool pattern_contains_choice_subpatterns(pattern *self);
bool pattern_is_correct(pattern *self);
type *pattern_get_type(void);
void pattern_finalize(object *parent);

#endif
