/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The command_manager class header.
*/

#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "lang/object.h"
#include "command/builtin.h"
#include "shell/shell.h"
#include "lang/string.h"
#include "util/list.h"
#include "type.h"
#include "base.h"

typedef struct command_manager command_manager;
typedef struct shell shell;
typedef enum redirection redirection;

enum redirection {
    REDIRECT_STANDARD,
    REDIRECT_READ,
    REDIRECT_WRITE
};

struct shell;

struct command_manager {
    object parent;
    list *builtins;
    shell *shell;
    int fd[2];
    int fd_in;
};

#define TYPE_COMMAND_MANAGER (command_manager_get_type())

#define CMD_MANAGER_SPAWN \
if (redirect != REDIRECT_STANDARD) { \
    pipe(fd); \
    self->fd[0] = fd[0]; \
    self->fd[1] = fd[1]; \
} \
pid_t process = fork(); \
if (process < 0) \
    exit(1); \
if (process == 0) { \
    if (redirect != REDIRECT_STANDARD) { \
        dup2(self->fd_in, 0); \
        if (redirect == REDIRECT_WRITE) dup2(fd[1], 1); \
        close(fd[0]); \
    } \
    execve(executable->value, args, env); \
    if (errno == 2) \
        console_errln("%s: Command not found.", args[0]); \
    if (errno == 8) \
        console_errln("%s: Exec format error. Wrong Architecture.", args[0]); \
    if (errno == 13) \
        console_errln("%s: Permission denied.", args[0]); \
    if (errno != 2 && errno != 8 && errno != 13) \
        perror(args[0]); \
    exit(1); \
} else { \
    int status; \
    if (redirect == REDIRECT_STANDARD || redirect == REDIRECT_READ) { \
        while (waitpid(process, &status, 0) != -1); \
        if (WIFSIGNALED(status)) { \
            int terminate_signal = WTERMSIG(status); \
            if (terminate_signal == 11) \
                console_errln("Segmentation fault"); \
            if (terminate_signal == 8) \
                console_errln("Floating exception"); \
            self->shell->last_return_value = 1; \
        } else { \
            self->shell->last_return_value = WEXITSTATUS(status); \
        } \
    } \
    if (redirect != REDIRECT_STANDARD) { \
        close(fd[1]); \
        self->fd_in = redirect == REDIRECT_READ ? 0 : fd[0]; \
    } \
}

#define CMD_MANAGER_CALL_BUILTIN \
node *node_ = self->builtins->head; \
while (node_ != NULL) { \
    builtin *builtin_ = (builtin *) node_->value; \
    if (!builtin_is(builtin_, name)) { \
        node_ = node_->next; \
        continue; \
    } \
    string *exit_cmd = string_new("exit"); \
    if ( \
        redirect == REDIRECT_STANDARD || \
        string_equals((object *) name, (object *) exit_cmd) \
    ) { \
        if (!builtin_prepare(builtin_, arguments)) { \
            self->shell->last_return_value = 1; \
            object_unref((object *) exit_cmd); \
            return (TRUE); \
        } \
        if (!builtin_execute(builtin_)) \
            self->shell->last_return_value = 1; \
        builtin_dispose(builtin_); \
        object_unref((object *) exit_cmd); \
        return (TRUE); \
    } \
    object_unref((object *) exit_cmd); \
    int fd[2]; \
    pipe(fd); \
    self->fd[0] = fd[0]; \
    self->fd[1] = fd[1]; \
    pid_t process = fork(); \
    if (process < 0) \
        exit(1); \
    if (process == 0) { \
        dup2(self->fd_in, 0); \
        if (redirect == REDIRECT_WRITE) dup2(fd[1], 1); \
        close(fd[0]); \
        if (!builtin_prepare(builtin_, arguments)) { \
            self->shell->last_return_value = 1; \
            return (TRUE); \
        } \
        if (!builtin_execute(builtin_)) \
            self->shell->last_return_value = 1; \
        builtin_dispose(builtin_); \
        exit(1); \
    } else { \
        while (wait(NULL) != -1); \
        close(fd[1]); \
        self->fd_in = redirect == REDIRECT_READ ? 0 : fd[0]; \
    } \
    return (TRUE); \
}

#define CMD_MANAGER_CALL_BIN \
for (int i = 0; dirs != NULL && dirs[i] != NULL; i++) { \
    string *str = string_add(dirs[i], file_sep); \
    string *tmp = string_add(str, name); \
    object_unref((object *) str); \
    str = tmp; \
    path *path_ = path_new_from_absolute(tmp); \
    file *file_ = file_new(path_); \
    if (!file_is_executable(file_)) { \
        object_unref((object *) path_); \
        object_unref((object *) file_); \
        object_unref((object *) str); \
        object_unref((object *) dirs[i]); \
        continue; \
    } \
    spawn(self, path_->value, arguments, redirect); \
    object_unref((object *) path_); \
    object_unref((object *) file_); \
    object_unref((object *) str); \
    object_unref((object *) dirs[i]); \
    for (i++; dirs[i] != NULL; i++) \
        object_unref((object *) dirs[i]); \
    object_unref((object *) paths); \
    object_unref((object *) path_sep); \
    object_unref((object *) file_sep); \
    free(dirs); \
    return (TRUE); \
}

#define CMD_MANAGER_CALL \
for (int i = 0; i < arguments->size; i++) { \
    if (!argument_is_accessible((argument *) tmp->value)) { \
        self->shell->last_return_value = 1; \
        object_unref((object *) str_path); \
        object_unref((object *) path_); \
        object_unref((object *) args); \
        return (TRUE); \
    } \
    string *str = argument_get_content((argument *) tmp->value); \
    if (is_regex(str)) { \
        regex *regex_ = NULL; \
        TRY { \
            regex_ = regex_new(str, path_); \
            list *matches = regex_research_matches(regex_); \
            node *tmp = matches->head; \
            while (tmp != NULL) { \
                list_push(args, tmp->value); \
                tmp = tmp->next; \
            } \
            object_unref((object *) matches); \
            object_unref((object *) regex_); \
        } CATCH (BAD_REGEX_PATTERN) { \
            console_errln("42sh: Bad regex pattern"); \
            self->shell->last_return_value = 1; \
            object_unref((object *) regex_); \
            object_unref((object *) str); \
            object_unref((object *) str_path); \
            object_unref((object *) path_); \
            object_unref((object *) args); \
            return (TRUE); \
        } \
        ETRY; \
    } else { \
        list_push(args, (object *) str); \
    } \
    object_unref((object *) str); \
    tmp = tmp->next; \
} \
object_unref((object *) str_path); \
object_unref((object *) path_); \
if (command_manager_call_builtin(self, name, args, redirect)) { \
    object_unref((object *) args); \
    return (TRUE); \
} \
if (command_manager_call_bin(self, name, args, redirect)) { \
    object_unref((object *) args); \
    return (TRUE); \
} \
if (command_manager_call_local_bin(self, name, args, redirect)) { \
    object_unref((object *) args); \
    return (TRUE); \
} \
object_unref((object *) args);

command_manager *command_manager_construct(type *object_type);
command_manager *command_manager_new(shell *shell);
void command_manager_register(command_manager *self, builtin *builtin_);
bool command_manager_call(
    command_manager *self, string *name, list *arguments, redirection redirect
);
bool command_manager_call_builtin(
    command_manager *self, string *name, list *arguments, redirection redirect
);
bool command_manager_call_bin(
    command_manager *self, string *name, list *arguments, redirection redirect
);
bool command_manager_call_local_bin(
    command_manager *self, string *name, list *arguments, redirection redirect
);
type *command_manager_get_type(void);
void command_manager_finalize(object *parent);

#endif
