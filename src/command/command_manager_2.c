/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The command_manager class.
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "command/command_manager.h"
#include "command/builtin.h"
#include "argument/argument.h"
#include "lang/object.h"
#include "lang/string.h"
#include "regex/regex.h"
#include "shell/shell.h"
#include "util/list.h"
#include "util/node.h"
#include "io/console.h"
#include "io/path.h"
#include "io/file.h"
#include "try.h"
#include "type.h"
#include "base.h"
#include "errno.h"

static char **list_to_array(string *first, list *arguments)
{
    char **args = malloc(sizeof(char *) * (arguments->size + 2));
    node *tmp = arguments->head;
    args[0] = first->value;

    for (int i = 0; i < arguments->size; i++) {

        string *str = (string *) tmp->value;
        args[i + 1] = string_clone_to_primitive(str);

        tmp = tmp->next;
    }
    args[arguments->size + 1] = NULL;

    return (args);
}

static void spawn(
    command_manager *self, string *executable,
    list *arguments, redirection redirect)
{
    char **args = list_to_array(executable, arguments);
    char **env = self->shell->environment->array;
    int fd[2];
    CMD_MANAGER_SPAWN;
    for (int i = 1; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

bool command_manager_call_builtin(
    command_manager *self, string *name, list *arguments, redirection redirect)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    CMD_MANAGER_CALL_BUILTIN;
    return (FALSE);
}

bool command_manager_call_bin(
    command_manager *self, string *name, list *arguments, redirection redirect)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);

    string *paths = environment_get_path(self->shell->environment);
    string *path_sep = string_new(":");
    string *file_sep = string_new("/");
    string **dirs = string_split(paths, path_sep);
    CMD_MANAGER_CALL_BIN;
    object_unref((object *) paths);
    object_unref((object *) path_sep);
    object_unref((object *) file_sep);
    free(dirs);
    return (FALSE);
}

bool command_manager_call_local_bin(
    command_manager *self, string *name, list *arguments, redirection redirect)
{
    RETURN_VAL_IF_FAIL(self != NULL, FALSE);
    path *path_ = NULL;
    if (name->value[0] == '/') {
        path_ = path_new_from_absolute(name);
    } else {
        string *pwd = environment_get_pwd(self->shell->environment);
        path *path_pwd = path_new_from_absolute(pwd);
        path_ = path_new_from_relative(path_pwd, name);
        object_unref((object *) path_pwd);
        object_unref((object *) pwd);
    }
    file *file_ = file_new(path_);
    spawn(self, name, arguments, redirect);
    object_unref((object *) path_);
    object_unref((object *) file_);
    return (TRUE);
}
