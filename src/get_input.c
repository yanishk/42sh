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
    if (sk->array_pipe[1] != NULL) {
        if (((sk->is_a_command == 1 && sk->is_command_executed == 0)) ||
            (sk->is_a_builtin == 1 && sk->is_command_executed == 0))
            execute_command_pipe(path, cpy_env, sk);
    }
}

void launch_ducks(char *path, char  **cpy_env, stock_t *sk)
{
    if (sk->array_duck[1] != NULL) {
        sk->array_space = word_array_delim(sk->array_duck[0], " \t\n");
        sk->array_space_snd = word_array_delim(sk->array_duck[1], " \t\n");
        execute_command_redirect(path, cpy_env, sk);
    }
    if (sk->array_reverse_duck[1] != NULL) {
        sk->array_space = word_array_delim(sk->array_reverse_duck[0], " \t\n");
        sk->array_space_snd =
        word_array_delim(sk->array_reverse_duck[1], " \t\n");
        execute_command_reverse_redirect(path, cpy_env, sk);
    }
}

void launch_command(char *path, char  **cpy_env, stock_t *sk,
char **array_logical_and)
{
    for (int x = 0; array_logical_and[x] != NULL; x += 1) {
        sk->array_space =
        word_array_delim(array_logical_and[x], " \t\n");
        if (((sk->is_a_command == 1 && sk->is_command_executed == 0)) ||
            (sk->is_a_builtin == 1 && sk->is_command_executed == 0))
            execute_command(path, cpy_env, sk);
    }
}

void main_exec(stock_t *sk, char *path, char  **cpy_env)
{
    sk->is_a_command = 1;
    sk->is_command_executed = 0;
    char **array_logical_and = NULL;

    for (sk->index = 0; sk->array_virg[sk->index]; sk->index += 1) {
        count_duck(sk);
        sk->array_pipe = word_array_delim(sk->array_virg[sk->index], "|");
        sk->array_duck = word_array_delim(sk->array_virg[sk->index], ">");
        sk->array_reverse_duck =
        word_array_delim(sk->array_virg[sk->index], "<");
        array_logical_and = word_array_delim(sk->array_virg[sk->index], "&");
        launch_pipe(path, cpy_env, sk);
        launch_ducks(path, cpy_env, sk);
        if (sk->array_duck[1] == NULL && sk->array_reverse_duck[1] == NULL
            && sk->array_pipe[1] == NULL)
            launch_command(path, cpy_env, sk, array_logical_and);
    }
    free_main_exec(sk);
}

void get_input(stock_t *sk, char *path, char  **cpy_env)
{
    sk->buffer = NULL;
    sk->number_command = 0;
    size_t bufsize = 0;

    print_prompt();
    while (getline(&sk->buffer, &bufsize, stdin) != -1) {
        if (my_strlen(sk->buffer) == 1) {
            print_prompt();
            continue;
        }
        sk->is_a_builtin = 0;
        read_alias(sk);
        sk->array_virg = word_array_delim(sk->buffer, ";");
        main_exec(sk, path, cpy_env);
        print_prompt();
        free_array(sk->array_virg);
    }
    free(sk->buffer);
}
