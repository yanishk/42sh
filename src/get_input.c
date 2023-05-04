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
    if (sk->array_st.pipe[1] != NULL) {
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

void launch_command(char *path, char  **cpy_env, stock_t *sk,
char **array_logical_and)
{
    for (int x = 0; array_logical_and[x] != NULL; x += 1) {
        sk->array_st.space =
        word_array(array_logical_and[x], " \t\n");
        if (((sk->check_st.is_a_command == 1 &&
            sk->check_st.is_command_exec == 0)) ||
            (sk->check_st.is_a_builtin == 1 &&
            sk->check_st.is_command_exec == 0))
            execute_command(path, cpy_env, sk);
    }
}

void main_exec(stock_t *sk, char *path, char  **cpy_env)
{
    sk->check_st.is_a_command = 1;
    sk->check_st.is_command_exec = 0;
    char **array_logical_and = NULL;

    for (int i = 0; sk->array_st.virg[i]; i += 1) {
        sk->array_st.pipe = word_array(sk->array_st.virg[i], "|");
        sk->array_st.duck = word_array(sk->array_st.virg[i], ">");
        sk->array_st.reverse_duck = word_array(sk->array_st.virg[i], "<");
        array_logical_and = word_array(sk->array_st.virg[i], "&");
        count_duck(sk, i);
        launch_pipe(path, cpy_env, sk);
        launch_ducks(path, cpy_env, sk);
        if (sk->array_st.duck[1] == NULL && sk->array_st.reverse_duck[1] == NULL
            && sk->array_st.pipe[1] == NULL)
            launch_command(path, cpy_env, sk, array_logical_and);
    }
    free_main_exec(sk);
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
        read_alias(sk);
        sk->array_st.virg = word_array(sk->array_st.buffer, ";");
        main_exec(sk, path, cpy_env);
        print_prompt();
        free_array(sk->array_st.virg);
    }
    free(sk->array_st.buffer);
}
