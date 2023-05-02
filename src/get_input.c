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
    for (sk->index = 0; sk->array_virg[sk->index]; sk->index += 1) {
        sk->count_duck = 0;
        count_duck(sk);
        sk->array_pipe = word_array_delim(sk->array_virg[sk->index], "|");
        if (sk->array_pipe[1] != NULL) {
            execute_command_pipe(path, cpy_env, sk);
        }
        sk->array_duck = word_array_delim(sk->array_virg[sk->index], ">");
        if (sk->array_duck[1] != NULL) {
            sk->array_space = word_array_delim(sk->array_duck[0], " \t\n");
            sk->array_space_snd = word_array_delim(sk->array_duck[1], " \t\n");
            execute_command_redirect(path, cpy_env, sk);
        }
        if (sk->array_duck[1] == NULL && sk->array_pipe[1] == NULL) {
            sk->check = 0;
            sk->array_space =
            word_array_delim(sk->array_virg[sk->index], " \t\n");
            execute_command(path, cpy_env, sk);
        }
    }
}

void get_input(stock_t *sk, char *path, char  **cpy_env)
{
    sk->buffer = NULL;
    size_t bufsize = 0;

    print_prompt();
    while (getline(&sk->buffer, &bufsize, stdin) != -1) {
        if (my_strlen(sk->buffer) == 1) {
            print_prompt();
            continue;
        }
        read_alias(sk);
        sk->array_virg = word_array_delim(sk->buffer, ";");
        main_exec(sk, path, cpy_env);
        print_prompt();
    }
}
