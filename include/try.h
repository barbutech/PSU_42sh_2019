/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** The try file.
*/

#ifndef TRY_H
#define TRY_H

#include <stdio.h>
#include <setjmp.h>

#define TRY \
    { \
    jmp_buf local_jmp_buf; \
    jmp_buf *old_jmp_buf = active_jmp_buf; \
    active_jmp_buf = &local_jmp_buf; \
    int exception = setjmp(local_jmp_buf); \
    switch (exception) { \
    case 0: \
    while (1) {

#define THROW(x) longjmp(*active_jmp_buf, x);

#define CATCH(x) \
    break; \
    case x: \
    active_jmp_buf = old_jmp_buf;

#define CATCH_OTHERS \
    break; \
    default: \
    active_jmp_buf = old_jmp_buf;

#define FINALLY \
    break; \
    } \
    { \

#define ETRY \
    break; \
    } \
    } \
    active_jmp_buf = old_jmp_buf; \
    }

typedef enum exceptions exceptions;

enum exceptions {
    EXCEPTIONS,
    PREMATURE_END_ERR,
    UNKNOWN_TOKEN_ERR,
    UNEXPECTED_TOKEN_ERR,
    UNKNOWN_INSTRUCTION_ERR,
    UNEXPECTED_INSTRUCTION_ERR,
    INVALID_NULL_CMD_ERR,
    SYSCALL_ERR,
    BAD_REGEX_PATTERN
};

jmp_buf *active_jmp_buf;

#endif
