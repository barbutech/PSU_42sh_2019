/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The base utility.
*/

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#define RETURN_IF_FAIL(expr) if ((expr) == FALSE) { \
        return; \
    }

#define RETURN_VAL_IF_FAIL(expr, val) if ((expr) == FALSE) { \
        return (val); \
    }

#ifndef BASE_H
#define BASE_H

typedef unsigned char byte;

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;

typedef int bool;

#endif
