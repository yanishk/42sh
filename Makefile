##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

SRC	=	main.c 	\
		src/get_input.c 	\
		src/pars_env.c 	\
		src/creating_cd.c 	\
		src/create_path_oldpwd.c 	\
		src/env.c 	\
		src/loop_buffer.c 	\
		src/set_env.c 	\
		src/error_handling.c 	\
		src/env_command.c 	\
		src/unset_command.c 	\
		src/redirection.c	\
		src/count_duck.c	\
		src/execute_binary.c 	\
		src/pipe.c 	\
		lib/my_putstr.c 	\
		lib/my_putchar.c 	\
		lib/my_str_to_word_array.c 	\
		lib/my_str_to_word_array_virg.c 	\
		lib/my_str_to_word_array_duck.c 	\
		lib/my_str_to_word_array_pipe.c 	\
		lib/my_word_array_two_dots.c 	\
		lib/my_strcomp.c 	\
		lib/my_strcomp_wo_len.c 	\
		lib/my_strlen.c 	\
		lib/my_strcat.c 	\
		lib/my_strcpy.c 	\
		lib/my_strdup.c 	\

OBJ	=	$(SRC:.c=.o)

CPPFLAGS = -I include

CFLAGS = -g3

NAME	=	42sh

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CPPLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	 fclean all
