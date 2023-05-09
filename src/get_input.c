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

void main_exec(stock_t *sk, char *path, char  **cpy_env)
{
    sk->check_st.is_a_command = 1;
    sk->check_st.is_command_exec = 0;
    sk->check_st.is_double_pipe = 0;
    for (int i = 0; sk->array_st.virg[i] && sk->check_st.is_a_builtin != 84; i += 1) {
        sk->array_st.pipe = word_array(sk->array_st.virg[i], "|");
        sk->array_st.double_and = word_array(sk->array_st.virg[i], ";&");
        sk->array_st.alias = sk->array_st.double_and;
        read_alias(sk, 0);
        count_duck(sk, i);
        count_pipe(sk, i);
        if (sk->array_st.pipe[1] != NULL && sk->check_st.is_double_pipe == 0)
            execute_command_pipe(path, cpy_env, sk);
        else
            check_command_type(path, cpy_env, sk);
    }
}

void get_input(stock_t *sk, char *path, char  **cpy_env)
{
    sk->array_st.buffer = NULL;
    sk->check_st.number_command = 0;
    size_t bufsize = 0;

    print_prompt();
    while (getline(&sk->array_st.buffer, &bufsize, stdin) != -1) {
        if (my_strlen(sk->array_st.buffer) == 1) {
            print_prompt();
            continue;
        }
        sk->check_st.is_a_builtin = 0;
        sk->array_st.virg = word_array(sk->array_st.buffer, ";");
        sk->array_st.alias =sk->array_st.virg;
        read_alias(sk, 0);
        main_exec(sk, path, cpy_env);
        print_prompt();
    }
}
