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

string *string_new(char *value)
{
    int length = 0;
    for (; value[length] != '\0'; length++);

    return (string_new_with_length(value, length));
}

string *string_new_with_length(char *value, int length)
{
    return (string_new_with_range(value, 0, length));
}

string *string_new_with_range(char *value, int start, int end)
{
    string *self = string_construct(TYPE_STRING);
    RETURN_VAL_IF_FAIL(self != NULL, NULL);

    self->length = end - start;
    self->value = malloc(sizeof(char) * (self->length + 1));

    for (int i = 0; i < self->length; i++)
        self->value[i] = value[start + i];

    self->value[self->length] = '\0';

    return (self);
}

string *string_new_from_int(int n)
{
    char buffer[11];
    for (int i = 0; i < 11; i++)
        buffer[i] = '\0';

    int index = 0;

    do {
        buffer[index] = (n % 10) + '0';
        n /= 10;
        index++;
    } while (n != 0);

    for (int i = 0, j = index - 1; i < j; i++, j--) {
        char c = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = c;
    }

    return (string_new(buffer));
}
