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

int exit_sh(stock_t *sk)
{
    int res = my_strcomp(sk->array_space[0], "exit");

    if (res == 0)
        exit (0);
    return 0;
}

void main_exec(char **env, stock_t *sk, char *path, char ***cpy_env)
{
    for (sk->index = 0; sk->array_virg[sk->index]; sk->index += 1) {
        sk->count_duck = 0;
        count_duck(sk);
        sk->array_pipe = my_str_to_word_array_pipe(sk->array_virg[sk->index]);
        if (sk->array_pipe[1] != NULL) {
            execute_command_pipe(env, path, cpy_env, sk);
        }
        sk->array_duck = my_str_to_word_array_duck(sk->array_virg[sk->index]);
        if (sk->array_duck[1] != NULL) {
            sk->array_space = my_str_to_word_array(sk->array_duck[0]);
            sk->array_space_snd = my_str_to_word_array(sk->array_duck[1]);
            execute_command_redirect(env, path, cpy_env, sk);
        }
        if (sk->array_duck[1] == NULL && sk->array_pipe[1] == NULL) {
            sk->check = 0;
            sk->array_space = my_str_to_word_array(sk->array_virg[sk->index]);
            execute_command(env, path, cpy_env, sk);
        }
    }
}

void get_input(char **env, stock_t *sk, char *path, char ***cpy_env)
{
    sk->buffer = NULL;
    size_t bufsize = 0;

    my_putstr("$> ");
    while (getline(&sk->buffer, &bufsize, stdin) != -1) {
        if (my_strlen(sk->buffer) == 1) {
            my_putstr("$> ");
            continue;
        }
        sk->array_virg = my_str_to_word_array_virg(sk->buffer);
        main_exec(env, sk, path, cpy_env);
        my_putstr("$> ");
    }
}
