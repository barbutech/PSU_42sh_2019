
SRC = src/aliases/alias.c \
      src/aliases/alias_interact.c \
      src/aliases/alias_init.c \
      src/argument/argument.c \
      src/argument/plain_argument.c \
      src/argument/tokenized_argument.c \
      src/argument/variable_argument_1.c \
      src/argument/variable_argument_2.c \
      src/command/alias_builtin_1.c \
      src/command/alias_builtin_2.c \
      src/command/builtin_1.c \
      src/command/builtin_2.c \
      src/command/cd_builtin_1.c \
      src/command/cd_builtin_2.c \
      src/command/command_manager_1.c \
      src/command/command_manager_2.c \
      src/command/command_manager_3.c \
      src/command/echo_builtin_1.c \
      src/command/echo_builtin_2.c \
      src/command/env_builtin_1.c \
      src/command/env_builtin_2.c \
      src/command/exit_builtin_1.c \
      src/command/exit_builtin_2.c \
      src/command/repeat_builtin_1.c \
      src/command/repeat_builtin_2.c \
      src/command/set_var_builtin_1.c \
      src/command/set_var_builtin_2.c \
      src/command/setenv_builtin_1.c \
      src/command/setenv_builtin_2.c \
      src/command/setenv_builtin_3.c \
	  src/command/unalias_builtin_1.c \
      src/command/unalias_builtin_2.c \
      src/command/unsetenv_builtin_1.c \
      src/command/unsetenv_builtin_2.c \
      src/command/where_builtin_1.c \
      src/command/where_builtin_2.c \
      src/command/where_builtin_3.c \
      src/command/which_builtin_1.c \
      src/command/which_builtin_2.c \
      src/command/which_builtin_3.c \
      src/env/environment_1.c \
      src/env/environment_2.c \
      src/env/environment_3.c \
      src/env/environment_4.c \
      src/format/chararray_format_1.c \
      src/format/chararray_format_2.c \
      src/format/format.c \
      src/format/formatter.c \
      src/format/int_format_1.c \
      src/format/int_format_2.c \
      src/format/string_format_1.c \
      src/format/string_format_2.c \
      src/instruction/command.c \
      src/instruction/instruction.c \
      src/instruction/text.c \
      src/interpreter/interpreter_1.c \
      src/interpreter/interpreter_2.c \
      src/interpreter/interpreter_3.c \
      src/interpreter/interpreter_4.c \
      src/io/console.c \
      src/io/file_1.c \
      src/io/file_2.c \
      src/io/path_1.c \
      src/io/path_2.c \
      src/io/path_3.c \
      src/lang/object_1.c \
      src/lang/object_2.c \
      src/lang/string_1.c \
      src/lang/string_2.c \
      src/lang/string_3.c \
      src/lang/string_4.c \
      src/lexer/lexer_1.c \
      src/lexer/lexer_2.c \
      src/lexer/token.c \
      src/parser/parser_1.c \
      src/parser/parser_2.c \
      src/parser/parser_3.c \
      src/parser/parser_4.c \
      src/parser/parser_5.c \
      src/parser/parser_6.c \
	  src/regex/pattern_1.c \
      src/regex/pattern_2.c \
      src/regex/pattern_3.c \
      src/regex/regex_1.c \
      src/regex/regex_2.c \
      src/shell/main.c \
	  src/shell/shell_1.c \
	  src/shell/shell_2.c \
      src/shell/shell_3.c \
      src/util/array_1.c \
      src/util/array_2.c \
      src/util/entry.c \
      src/util/list_1.c \
      src/util/list_2.c \
      src/util/list_3.c \
      src/util/map_1.c \
      src/util/map_2.c \
      src/util/map_3.c \
      src/util/node.c \
      src/util/stack_1.c \
      src/util/stack_2.c \
      src/util/tree.c \
      src/var/variable_manager_1.c \
      src/var/variable_manager_2.c \
      src/type_1.c \
      src/type_2.c

OBJ = $(SRC:.c=.o)

NAME = 42sh

CFLAGS = -Wall -Iinclude -g
CC = gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	$(MAKE) clean
