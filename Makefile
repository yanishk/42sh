##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

SRC	=	main.c 								\
		src/get_input.c 					\
		src/find_exec.c 					\
		src/pars_env.c 						\
		src/creating_cd.c 					\
		src/create_path_oldpwd.c 			\
		src/env.c 							\
		src/loop_buffer.c 					\
		src/set_env.c 						\
		src/error_handling.c 				\
		src/env_command.c 					\
		src/unset_command.c 				\
		src/redirection.c					\
		src/count_duck.c					\
		src/execute_binary.c 				\
		src/exit_shell.c 					\
		src/pipe.c 							\
		lib/word_array_delimiter.c 			\
		lib/word_array_delimiter2.c 		\
		lib/print_free_array.c 				\
		lib/my_putstr.c 					\
		lib/my_putchar.c 					\
		lib/my_getnbr.c 					\
		lib/my_strcomp.c 					\
		lib/my_strcomp_wo_len.c 			\
		lib/my_strlen.c 					\
		lib/my_strcat.c 					\
		lib/my_strcpy.c 					\
		lib/my_strdup.c 					\

CC ?= gcc

OBJ	=	$(SRC:.c=.o)

RM = rm -f

CPPFLAGS += -iquote./include

CFLAGS += -Wall -Wextra -g

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
