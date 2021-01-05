/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The string class.
*/

#include <stdlib.h>
#include "lang/string.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

string *string_substring(string *self, int start, int end)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    return (string_new_with_range(self->value, start, end));
}

int string_index_of(string *self, string *needle)
{
    RETURN_VAL_IF_FAIL(self != NULL, -1);

    for (int i = 0; i < self->length - needle->length + 1; i++) {
        int j = 0;
        for (
            ; self->value[i + j] == needle->value[j] && i + j < self->length;
            j++
        );
        if (j == needle->length)
            return (i);
    }
    return (-1);
}

int string_count_occurences(string *self, string *needle)
{
    RETURN_VAL_IF_FAIL(self != NULL, 0);

    int counter = 0;
    if (needle->length == 0)
        return (0);
    for (int i = 0; i < self->length - needle->length + 1; i++) {
        int j = 0;
        while (self->value[i + j] == needle->value[j] &&
            self->value[i + j] != '\0')
            j++;
        if (needle->value[j] == '\0') {
            counter++;
            i += j - 1;
        }
    }
    return (counter);
}

string **string_split(string *self, string *separator)
{
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    STRING_SPLIT;
    return (array);
}
