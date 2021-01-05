/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The repeat_builtin class header.
*/

#ifndef REPEAT_BUILTIN_H
#define REPEAT_BUILTIN_H

#include "command/builtin.h"
#include "command/command_manager.h"
#include "lang/object.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct repeat_builtin repeat_builtin;

struct repeat_builtin {
    builtin parent;
    command_manager *cmd_manager;
    int n;
    string *name;
    list *args;
};

#define TYPE_REPEAT_BUILTIN (repeat_builtin_get_type())

#define REPEAT_BUILTIN_PREPARE \
node *tmp = arguments->head; \
self->n = string_to_int((string *) tmp->value); \
tmp = tmp->next; \
if (self->n == -1) { \
    console_errln("repeat: Badly formed number."); \
    return (FALSE); \
} \
object_unref((object *) self->name); \
self->name = (string *) tmp->value; \
object_ref((object *) self->name); \
tmp = tmp->next; \
object_unref((object *) self->args); \
self->args = list_new(); \
while (tmp != NULL) { \
    plain_argument *arg = plain_argument_new((string *) tmp->value); \
    list_push(self->args, (object *) arg); \
    object_unref((object *) arg); \
    tmp = tmp->next; \
}

repeat_builtin *repeat_builtin_construct(type *object_type);
repeat_builtin *repeat_builtin_new(command_manager *cmd_manager);
bool repeat_builtin_prepare(builtin *parent, list *arguments);
bool repeat_builtin_execute(builtin *parent);
bool repeat_builtin_is(builtin *parent, string *name);
type *repeat_builtin_get_type(void);
void repeat_builtin_finalize(object *parent);

#endif
