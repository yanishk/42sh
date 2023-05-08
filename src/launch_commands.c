/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** get_input
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include "my.h"

void launch_ducks(char *path, char **cpy_env, stock_t *sk)
{
    if (sk->array_st.duck[1] != NULL) {
        sk->array_st.space = word_array(sk->array_st.duck[0], " \t\n");
        sk->array_st.space_snd = word_array(sk->array_st.duck[1], " \t\n");
        execute_command_redirect(path, cpy_env, sk);
    }
    if (sk->array_st.reverse_duck[1] != NULL) {
        sk->array_st.space = word_array(sk->array_st.reverse_duck[0], " \t\n");
        sk->array_st.space_snd =
        word_array(sk->array_st.reverse_duck[1], " \t\n");
        execute_command_reverse_redirect(path, cpy_env, sk);
    }
}

void launch_command(char *path, char **cpy_env, stock_t *sk, int y)
{
    if ((last_command_succeed(sk) && y == 0) || (last_command_failed(sk) &&
        sk->check_st.is_double_pipe > 0 && y > 0)) {
        if (sk->array_st.duck[1] == NULL &&
            sk->array_st.reverse_duck[1] == NULL) {
            execute_command(path, cpy_env, sk);
        } else {
            launch_ducks(path, cpy_env, sk);
        }
    }
}

void check_command_type(char *path, char **cpy_env, stock_t *sk)
{
    for (int x = 0; sk->array_st.double_and[x] != NULL; x += 1) {
        sk->array_st.double_pipe = word_array(sk->array_st.double_and[x], "|");
        for (int y = 0; sk->array_st.double_pipe[y] != NULL; y += 1) {
            sk->array_st.duck =
            word_array(sk->array_st.double_pipe[y], ">");
            sk->array_st.reverse_duck =
            word_array(sk->array_st.double_pipe[y], "<");
            sk->array_st.space =
            word_array(sk->array_st.double_pipe[y], " \t\n");
            launch_command(path, cpy_env, sk, y);
        }
    }
}
