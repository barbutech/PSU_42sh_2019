/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The entry class.
*/

#include "util/entry.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

entry *entry_construct(type *object_type)
{
    entry *self = (entry *) object_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &entry_finalize;

    return (self);
}

entry *entry_new(object *key, object *value)
{
    entry *self = entry_construct(TYPE_ENTRY);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref(key);
    object_ref(value);

    self->key = key;
    self->value = value;

    return (self);
}

object *entry_get_value(entry *self)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref(self->value);

    return (self->value);
}

type *entry_get_type(void)
{
    return (type_register(
        "util.entry",
        sizeof(entry),
        TYPE_OBJECT
    ));
}

void entry_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    entry *self = (entry *) parent;

    object_unref(self->key);
    object_unref(self->value);

    object_finalize(parent);
}
