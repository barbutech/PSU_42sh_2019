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

regex *regex_construct(type *object_type)
{
    regex *self = (regex *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &regex_finalize;

    return (self);
}

regex *regex_new(string *expression, path *path_)
{
    pattern *pattern_ = pattern_new(expression);
    list *next_patterns = list_new();

    if (!pattern_is_correct(pattern_)) {
        object_unref((object *) pattern_);
        object_unref((object *) next_patterns);

        THROW(BAD_REGEX_PATTERN);
    }

    regex *self = regex_new_with_pattern(path_, path_, pattern_, next_patterns);

    object_unref((object *) pattern_);
    object_unref((object *) next_patterns);

    return (self);
}

regex *regex_new_with_pattern(path *path_, path *base_path,
    pattern *pattern_, list *next_patterns)
{
    regex *self = regex_construct(TYPE_REGEX);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    if (!pattern_is_correct(pattern_))
        THROW(BAD_REGEX_PATTERN);

    object_ref((object *) path_);
    object_ref((object *) base_path);
    object_ref((object *) pattern_);
    object_ref((object *) next_patterns);

    self->path = path_;
    self->base_path = base_path;
    self->pattern = pattern_;
    self->next_patterns = next_patterns;

    return (self);
}

type *regex_get_type(void)
{
    return (type_register(
        "regex.regex",
        sizeof(regex),
        TYPE_OBJECT
    ));
}

void regex_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    regex *self = (regex *) parent;

    object_unref((object *) self->path);
    object_unref((object *) self->base_path);
    object_unref((object *) self->pattern);
    object_unref((object *) self->next_patterns);

    object_finalize(parent);
}
