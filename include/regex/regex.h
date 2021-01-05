/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The regex class header.
*/

#ifndef REGEX_H
#define REGEX_H

#include "regex/pattern.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "io/path.h"
#include "type.h"
#include "base.h"

typedef struct regex regex;

struct regex {
    object parent;
    path *path;
    path *base_path;
    pattern *pattern;
    list *next_patterns;
};

#define TYPE_REGEX (regex_get_type())

#define REGEX_MATCH \
list *matched_files = regex_get_matched_files(self); \
if (matched_files->size == 0) { \
    object_unref((object *) subpatterns); \
    object_unref((object *) matched_files); \
    return (matches); \
} else if (matched_files->size > 1) { \
    string *separator = string_new("/"); \
    node *tmp = matched_files->head; \
    while (tmp != NULL) { \
        string *str = (string *) tmp->value; \
        path *new_path = path_new_from_absolute(self->path->value); \
        list *next_patterns = list_new(); \
        pattern *pattern_ = pattern_new(str); \
        node *tmp2 = self->next_patterns->head; \
        while (tmp2 != NULL) { \
            list_push(next_patterns, tmp2->value); \
            tmp2 = tmp2->next; \
        } \
        regex *regex_ = regex_new_with_pattern(new_path, self->base_path, \
            pattern_, next_patterns); \
        list *new_matches = regex_research_matches(regex_); \
        list_merge(matches, new_matches); \
        object_unref((object *) new_matches); \
        object_unref((object *) regex_); \
        object_unref((object *) pattern_); \
        object_unref((object *) next_patterns); \
        object_unref((object *) new_path); \
        tmp = tmp->next; \
    } \
    object_unref((object *) separator); \
    object_unref((object *) matched_files); \
    return (matches); \
} \
node *patterns = self->next_patterns->head; \
string *separator = string_new("/"); \
if (patterns == NULL) { \
    string *str = (string *) matched_files->head->value; \
    string *new_path_str = NULL; \
    string *tmp2 = NULL; \
    new_path_str = string_add(self->path->value, separator); \
    tmp2 = string_add(new_path_str, str); \
    object_unref((object *) new_path_str); \
    object_ref((object *) tmp2); \
    new_path_str = tmp2; \
    path *new_path = path_new_from_absolute(new_path_str); \
    string *relative_path = \
        path_create_relative_path(self->base_path, new_path); \
    list_push(matches, (object *) relative_path); \
    object_unref((object *) new_path); \
    object_unref((object *) relative_path); \
    object_unref((object *) new_path_str); \
    object_unref((object *) tmp2); \
    object_unref((object *) separator); \
    object_unref((object *) matched_files); \
    return (matches); \
} \
string *new_path_str = NULL; \
string *tmp2 = NULL; \
new_path_str = string_add(self->path->value, separator); \
tmp2 = string_add(new_path_str, self->pattern->content); \
object_unref((object *) new_path_str); \
object_ref((object *) tmp2); \
new_path_str = tmp2; \
list *next_patterns = list_new(); \
path *path_ = path_new_from_absolute(new_path_str); \
pattern *pattern_ = pattern_new(((pattern *) patterns->value)->content); \
patterns = patterns->next; \
while (patterns != NULL) { \
    list_push(next_patterns, patterns->value); \
    patterns = patterns->next; \
} \
node *tmp3 = next_patterns->head; \
while (tmp3 != NULL) { \
    tmp3 = tmp3->next; \
} \
regex *regex_ = regex_new_with_pattern(path_, self->base_path, \
    pattern_, next_patterns); \
list *new_matches = regex_research_matches(regex_); \
list_merge(matches, new_matches); \
object_unref((object *) new_matches); \
object_unref((object *) regex_); \
object_unref((object *) path_); \
object_unref((object *) pattern_); \
object_unref((object *) next_patterns); \
object_unref((object *) tmp2); \
object_unref((object *) new_path_str); \
object_unref((object *) separator); \
object_unref((object *) matched_files);

#define REGEX_RESEARCH \
list *matches = list_new(); \
list *subpatterns = pattern_extract_subpatterns(self->pattern); \
if (pattern_contains_hierarchical_subpatterns(self->pattern)) { \
    list *next_patterns = list_new(); \
    node *tmp = subpatterns->head->next; \
    while (tmp != NULL) { \
        list_push(next_patterns, tmp->value); \
        tmp = tmp->next; \
    } \
    tmp = self->next_patterns->head; \
    while (tmp != NULL) { \
        list_push(next_patterns, tmp->value); \
        tmp = tmp->next; \
    } \
    path *path_ = path_new_from_absolute(self->path->value); \
    pattern *pattern_ = (pattern *) subpatterns->head->value; \
    regex *regex_ = regex_new_with_pattern(path_, self->base_path, \
        pattern_, next_patterns); \
    list *new_matches = regex_research_matches(regex_); \
    list_merge(matches, new_matches); \
    object_unref((object *) new_matches); \
    object_unref((object *) path_); \
    object_unref((object *) regex_); \
    object_unref((object *) next_patterns); \
} else if (pattern_contains_choice_subpatterns(self->pattern)) { \
    node *tmp = subpatterns->head; \
    while (tmp != NULL) { \
        path *path_ = path_new_from_absolute(self->path->value); \
        list *next_patterns = list_new(); \
        node *tmp2 = self->next_patterns->head; \
        while (tmp2 != NULL) { \
            list_push(next_patterns, tmp2->value); \
            tmp2 = tmp2->next; \
        } \
        pattern *pattern_ = (pattern *) tmp->value; \
        regex *regex_ = regex_new_with_pattern(path_, self->base_path, \
            pattern_, next_patterns); \
        list *new_matches = regex_research_matches(regex_); \
        list_merge(matches, new_matches); \
        object_unref((object *) new_matches); \
        object_unref((object *) path_); \
        object_unref((object *) next_patterns); \
        object_unref((object *) regex_); \
        tmp = tmp->next; \
    } \
} else { \
    REGEX_MATCH; \
} \
object_unref((object *) subpatterns);

regex *regex_construct(type *object_type);
regex *regex_new(string *expression, path *path_);
regex *regex_new_with_pattern(path *path_, path *base_path,
    pattern *pattern_, list *next_patterns);
list *regex_research_matches(regex *self);
type *regex_get_type(void);
void regex_finalize(object *parent);

#endif
