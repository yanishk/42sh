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
#include "my.h"

void launch_pipe(char *path, char  **cpy_env, stock_t *sk)
{
    if (sk->array_st.pipe[1] != NULL && sk->check_st.is_double_pipe == 0) {
        if (((sk->check_st.is_a_command == 1 &&
        sk->check_st.is_command_exec == 0)) ||
            (sk->check_st.is_a_builtin == 1 &&
            sk->check_st.is_command_exec == 0))
            execute_command_pipe(path, cpy_env, sk);
    }
}

void launch_ducks(char *path, char  **cpy_env, stock_t *sk)
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

void launch_logical_and(char *path, char  **cpy_env, stock_t *sk)
{
    for (int x = 0; sk->array_st.array_logical_and[x] != NULL; x += 1) {
        sk->array_st.space =
        word_array(sk->array_st.array_logical_and[x], " \t\n");
        if (((sk->check_st.is_a_command == 1 &&
        sk->check_st.is_command_exec == 0)) ||
            (sk->check_st.is_a_builtin == 1 &&
            sk->check_st.is_command_exec == 0))
            execute_command(path, cpy_env, sk);
    }
}

void launch_double_pipe(char *path, char  **cpy_env, stock_t *sk)
{
    sk->check_st.is_command_exec = 1;

    for (int x = 0; sk->array_st.pipe[x] != NULL; x += 1) {
        sk->array_st.space = word_array(sk->array_st.pipe[x], " \t\n");
        if (((sk->check_st.is_a_command == 1 &&
        sk->check_st.is_command_exec == 1)) ||
            (sk->check_st.is_a_builtin == 1 &&
            sk->check_st.is_command_exec == 1) ||
            (sk->check_st.is_a_command == 0 &&
            sk->check_st.is_a_builtin == 0)) {
                sk->check_st.is_command_exec = 0;
                execute_command(path, cpy_env, sk);
            }
    }
}

void launch_command(char *path, char **cpy_env, stock_t *sk)
{
    if (sk->array_st.duck[1] == NULL && sk->array_st.reverse_duck[1] == NULL
        && sk->array_st.pipe[1] == NULL)
        launch_logical_and(path, cpy_env, sk);
    if (sk->array_st.pipe[1] != NULL && sk->check_st.is_double_pipe > 0)
        launch_double_pipe(path, cpy_env, sk);
}
