/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The text class.
*/

#include "instruction/text.h"
#include "instruction/instruction.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

text *text_construct(type *object_type)
{
    text *self = (text *) instruction_construct(object_type);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    ((object *) self)->finalize = &text_finalize;

    return (self);
}

text *text_new(string *content)
{
    text *self = text_construct(TYPE_TEXT);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    object_ref((object *) content);

    self->content = content;

    ((instruction *) self)->type = INSTRUCTION_TEXT;

    return (self);
}

type *text_get_type(void)
{
    return (type_register(
        "instruction.text",
        sizeof(text),
        TYPE_INSTRUCTION
    ));
}

void text_finalize(object *parent)
{
    RETURN_IF_FAIL(parent != NULL);
    text *self = (text *) parent;

    object_unref((object *) self->content);

    instruction_finalize(parent);
}
