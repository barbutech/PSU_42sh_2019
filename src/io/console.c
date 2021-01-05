/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The console utility.
*/

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "io/console.h"
#include "lang/string.h"
#include "format/formatter.h"
#include "type.h"
#include "base.h"

void console_print(int channel, string *message)
{
    write(channel, message->value, message->length);
}

void console_write(char *format, ...)
{
    va_list args;
    va_start(args, format);

    formatter *formatter_ = formatter_new();
    string *str = formatter_format(formatter_, format, args);

    console_print(1, str);

    va_end(args);
    object_unref((object *) str);
    object_unref((object *) formatter_);
}

void console_writeln(char *format, ...)
{
    console_write(format);
    write(1, "\n", 1);
}

void console_err(char *format, ...)
{
    va_list args;
    va_start(args, format);

    formatter *formatter_ = formatter_new();
    string *str = formatter_format(formatter_, format, args);

    console_print(2, str);

    va_end(args);
    object_unref((object *) str);
    object_unref((object *) formatter_);
}

void console_errln(char *format, ...)
{
    console_err(format);
    write(2, "\n", 1);
}
