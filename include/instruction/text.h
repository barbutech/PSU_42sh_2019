/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The text class header.
*/

#ifndef TEXT_H
#define TEXT_H

#include "instruction/instruction.h"
#include "lang/object.h"
#include "lang/string.h"
#include "type.h"
#include "base.h"

typedef struct text text;

struct text {
    instruction parent;
    string *content;
};

#define TYPE_TEXT (text_get_type())

text *text_construct(type *object_type);
text *text_new(string *content);
type *text_get_type(void);
void text_finalize(object *parent);

#endif
