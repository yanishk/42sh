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

void main_exec(stock_t *sk, char *cwd, char *path, char  **cpy_env)
{
    sk->check_st.is_a_command = 1;
    sk->check_st.is_command_exec = 0;
    sk->check_st.is_double_pipe = 0;

    for (int i = 0; sk->array_st.virg[i]; i += 1) {
        sk->array_st.pipe = word_array(sk->array_st.virg[i], "|");
        sk->array_st.duck = word_array(sk->array_st.virg[i], ">");
        sk->array_st.reverse_duck = word_array(sk->array_st.virg[i], "<");
        sk->array_st.array_logical_and = word_array(sk->array_st.virg[i], "&");
        count_duck(sk, i);
        count_pipe(sk, i);
        launch_pipe(cwd, path, cpy_env, sk);
        launch_ducks(cwd, path, cpy_env, sk);
        launch_command(cwd, path, cpy_env, sk);
    }
    free_main_exec(sk);
}

void get_input(stock_t *sk, char *cwd, char *path, char  **cpy_env)
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
        read_alias(sk);
        sk->array_st.virg = word_array(sk->array_st.buffer, ";");
        main_exec(sk, cwd, path, cpy_env);
        print_prompt();
        free_array(sk->array_st.virg);
    }
    free(sk->array_st.buffer);
}
