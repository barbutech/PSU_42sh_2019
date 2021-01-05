/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** The interpreter class header.
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lang/object.h"
#include "parser/parser.h"
#include "command/command_manager.h"
#include "var/variable_manager.h"
#include "util/list.h"
#include "util/tree.h"
#include "type.h"
#include "base.h"

typedef struct interpreter interpreter;

struct interpreter {
    object parent;
    command_manager *cmd_manager;
    variable_manager *var_manager;
    tree *statements;
};

#define TYPE_INTERPRETER (interpreter_get_type())

#define INTERPRETER_STATEMENT \
switch (instr->type) { \
    case INSTRUCTION_COMMAND: \
        interpreter_interprete_command(self, tree_, redirect); \
        break; \
    case INSTRUCTION_CONTINUATION: \
        interpreter_interprete_continuation(self, tree_); \
        break; \
    case INSTRUCTION_PIPE: \
        interpreter_interprete_pipe(self, tree_, redirect); \
        break; \
    case INSTRUCTION_OUT_REDIRECTION_TRUNCATE: \
        interpreter_interprete_out_redirection_truncate(self, tree_, redirect);\
        break; \
    case INSTRUCTION_OUT_REDIRECTION_APPEND: \
        interpreter_interprete_out_redirection_append(self, tree_, redirect); \
        break; \
    case INSTRUCTION_IN_REDIRECTION_FILE: \
        interpreter_interprete_in_redirection_file(self, tree_, redirect); \
        break; \
    case INSTRUCTION_IN_REDIRECTION_READ: \
        interpreter_interprete_in_redirection_read(self, tree_, redirect); \
        break; \
    case INSTRUCTION_AND: \
        interpreter_interprete_and(self, tree_); \
        break; \
    case INSTRUCTION_OR: \
        interpreter_interprete_or(self, tree_); \
        break; \
    default: \
        THROW(UNKNOWN_INSTRUCTION_ERR); \
}

#define INTERPRETER_OUT_TRUNCATE \
int fd = open(text_->content->value, O_CREAT, 0664); \
if (fd < 0) { \
    console_errln("%S: Permission denied."); \
    return; \
} \
close(fd); \
interpreter_interprete_statement(self, tree_->left, REDIRECT_WRITE); \
fd = open(text_->content->value, O_WRONLY | O_TRUNC); \
char buffer[250]; \
int len; \
while ((len = read(self->cmd_manager->fd_in, buffer, 249)) > 0) { \
    buffer[len] = '\0'; \
    write(fd, buffer, len); \
} \
close(fd);

#define INTERPRETER_IN_APPEND \
int fd = open(text_->content->value, O_CREAT, 0664); \
if (fd < 0) { \
    console_errln("%S: Permission denied."); \
    return; \
} \
close(fd); \
interpreter_interprete_statement(self, tree_->left, REDIRECT_WRITE); \
fd = open(text_->content->value, O_WRONLY | O_APPEND); \
char buffer[250]; \
int len; \
while ((len = read(self->cmd_manager->fd_in, buffer, 249)) > 0) { \
    buffer[len] = '\0'; \
    write(fd, buffer, len); \
} \
close(fd);

#define INTERPRETER_IN_FILE \
text *text_ = (text *) tree_->right->value; \
pipe(self->cmd_manager->fd); \
pid_t pid; \
if ((pid = fork()) == -1) { \
    THROW(SYSCALL_ERR); \
} \
else if (pid == 0) { \
    dup2(self->cmd_manager->fd_in, 0); \
    dup2(self->cmd_manager->fd[1], 1); \
    close(self->cmd_manager->fd[0]); \
    int fd = open(text_->content->value, O_RDONLY); \
    if (fd < 0) { \
        console_errln("%S: Permission denied."); \
        return; \
    } \
    char buffer[250]; \
    int len; \
    while ((len = read(fd, buffer, 249)) > 0) { \
        buffer[len] = '\0'; \
        write(1, buffer, len); \
    } \
    close(fd); \
    exit(1); \
} else { \
    close(self->cmd_manager->fd[1]); \
    self->cmd_manager->fd_in = self->cmd_manager->fd[0]; \
}

#define INTERPRETER_IN_READ \
text *text_ = (text *) tree_->right->value; \
pipe(self->cmd_manager->fd); \
pid_t pid; \
if ((pid = fork()) == -1) { \
    THROW(SYSCALL_ERR); \
} else if (pid == 0) { \
    close(self->cmd_manager->fd[0]); \
    char *buffer = NULL; \
    size_t len = 0; \
    ssize_t nread; \
    write(1, "? ", 2); \
    while ((nread = getline(&buffer, &len, stdin)) != -1) { \
        string *line = string_new_with_length(buffer, nread - 1); \
        if (object_equals((object *) text_->content, (object *) line)) { \
            break; \
            object_unref((object *) line); \
        } else { \
            write(self->cmd_manager->fd[1], buffer, nread); \
        } \
        write(1, "? ", 2); \
        object_unref((object *) line); \
    } \
    free(buffer); \
    exit(1); \
} else { \
    close(self->cmd_manager->fd[1]); \
    self->cmd_manager->fd_in = self->cmd_manager->fd[0]; \
}

interpreter *interpreter_construct(type *object_type);
interpreter *interpreter_new(
    parser *parser, command_manager *cmd_manager, variable_manager *var_manager
);
void interpreter_interprete(interpreter *self);
void interpreter_interprete_statement(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_command(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_pipe(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_out_redirection_truncate(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_out_redirection_append(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_in_redirection_file(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_in_redirection_read(
    interpreter *self, tree *tree_, redirection redirect);
void interpreter_interprete_continuation(interpreter *self, tree *tree_);
type *interpreter_get_type(void);
void interpreter_finalize(object *parent);
void interpreter_interprete_and(interpreter *self, tree *tree_);
void interpreter_interprete_or(interpreter *self, tree *tree_);

#endif
