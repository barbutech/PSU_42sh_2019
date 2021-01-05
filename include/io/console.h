/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** The console utility header.
*/

#ifndef CONSOLE_H
#define CONSOLE_H

#include "lang/string.h"
#include "type.h"
#include "base.h"

void console_print(int channel, string *message);
void console_write(char *format, ...);
void console_writeln(char *format, ...);
void console_err(char *format, ...);
void console_errln(char *format, ...);

#endif
