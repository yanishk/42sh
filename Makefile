##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

SRC	=	main.c 									\
		src/input/init_input.c					\
		src/input/get_input.c 					\
		src/input/input_manager.c 				\
		src/launch_commands.c 					\
		src/last_command_status.c 				\
		src/find_exec.c 						\
		src/creating_cd.c 						\
		src/create_path_oldpwd.c 				\
		src/loop_buffer.c 						\
		src/error_handling.c 					\
		src/redirection.c						\
		src/count_duck.c						\
		src/execute_binary.c 					\
		src/exit_shell.c 						\
		src/glob_exe.c	 						\
		src/display_prompt/fill_str.c			\
		src/display_prompt/get_size_term.c		\
		src/display_prompt/choice_prompt.c		\
		src/display_prompt/display_prompt.c		\
		src/display_prompt/display_prompt2.c	\
		src/pipe/pipe.c 						\
		src/pipe/exec_pipe.c 					\
		src/pipe/redirection_pipe.c 			\
		src/history/history.c					\
		src/history/history_command.c			\
		src/history/get_last_command_number.c 	\
		src/alias/read_alias.c					\
		src/alias/print_alias.c					\
		src/alias/add_alias.c					\
		src/alias/change_cmd.c					\
		src/free_all/free_main_exec.c			\
		src/env/setenv_error_handling.c 		\
		src/env/pars_env.c 						\
		src/env/my_unsetenv.c 					\
		src/env/my_setenv.c 					\
		src/env/print_env.c						\
		src/binary_flag/help.c					\
		src/binary_flag/list_flag.c				\
		src/binary_flag/help_flag.c				\
		src/echo/echo.c 						\
		src/echo/check_variables.c 				\
		src/echo/print_variable_value.c 		\
		src/arrow/handle_arrow.c				\
		src/arrow/arrow_up_down.c				\
		lib/word_array_delimiter.c 				\
		lib/word_array_delimiter2.c 			\
		lib/word_array_double.c 				\
		lib/print_free_array.c 					\
		lib/my_putstr.c 						\
		lib/my_putstr_error.c 					\
		lib/my_putchar.c 						\
		lib/my_getnbr.c 						\
		lib/my_strcomp.c 						\
		lib/my_strcomp_wo_len.c 				\
		lib/my_strlen.c 						\
		lib/my_strcat.c 						\
		lib/my_strcpy.c 						\
		lib/my_strdup.c 						\
		lib/my_swap_str.c 						\
		lib/my_revstr.c							\
		lib/my_int_to_str.c						\
		lib/colorize_str.c						\
		lib/len_tab.c							\

CC ?= gcc

OBJ	=	$(SRC:.c=.o)

RM = rm -f

CPPFLAGS += -iquote./include

CFLAGS += -Wall -Wextra

NAME	=	42sh

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPLAGS) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	 fclean all

.PHONY = all clean fclean re
