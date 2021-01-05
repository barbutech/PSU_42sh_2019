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

pattern *pattern_construct(type *object_type)
{
    pattern *self = (pattern *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &pattern_finalize;

    return (self);
}

pattern *pattern_new(string *content)
{
    pattern *self = pattern_construct(TYPE_PATTERN);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) content);
    self->content = content;

    return (self);
}

type *pattern_get_type(void)
{
    return (type_register(
        "regex.pattern",
        sizeof(pattern),
        TYPE_OBJECT
    ));
}

void pattern_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    pattern *self = (pattern *) parent;

    object_unref((object *) self->content);

    object_finalize(parent);
}
