/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The main file.
*/

#include <stdio.h>
#include "shell/shell.h"
#include "lang/object.h"
#include "type.h"
#include "base.h"

int main(int argc, char **argv, char **env)
{
    FILE *stream = stdin;
    bool execute_from_script = argc > 1;
    if (execute_from_script) {
        stream = fopen(argv[1], "r");
        RETURN_VAL_IF_FAIL(stream != NULL, 1);
    }
    shell *shell_ = shell_new(stream);
    shell_init(shell_, env);
    shell_start(shell_);
    shell_loop(shell_);
    shell_exit(shell_);

    object_unref((object *) shell_);

    if (execute_from_script)
        fclose(stream);

    return (0);
}
