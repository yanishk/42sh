/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int exist_in_env(char **cpy_env, char **array)
{
    char *line = my_strdup_str(array[1], '=');

    for (int i = 0; cpy_env[i] != NULL; i++) {
        if (my_strcomp_wo_len(cpy_env[i], line) == 0) {
            return (0);
        }
    }
    return (1);
}

void remove_or_change_line(char **old_env, char **cpy_env, char **array)
{
    char *line = NULL;
    int nb_of_lines = 0;
    int line_exist = 1;
    int number = 0;
    int i = 0;

    for (nb_of_lines = 0; old_env[nb_of_lines] != NULL; nb_of_lines++) {}
    for (int i = 0; i != nb_of_lines; i++)
        cpy_env[i] = my_strdup(old_env[i]);
    for (i = 0; array[i] != NULL; i++) {}
    line = my_strdup_str(array[1], '=');
    for (nb_of_lines = 0; cpy_env[nb_of_lines]; nb_of_lines++) {
        line_exist = my_strcomp_wo_len(cpy_env[nb_of_lines], line);
        if (line_exist == 0)
            number = nb_of_lines;
    }
    cpy_env[number] = NULL;
    for (int i = number; i != nb_of_lines - 1; i++)
        my_swap_str(&cpy_env[i], &cpy_env[i + 1]);
}

void my_unsetenv(char **cpy_env, char **array, stock_t *sk)
{
    char **old_env = NULL;
    int is_unsetenv = my_strcomp("unsetenv", array[0]);
    int is_in_myenv = 1;
    int i = 0;

    for (i = 0; array[i] != NULL; i++) {}
    if (is_unsetenv == 0) {
        sk->check_st.is_a_builtin = 1;
        if (i == 1) {
            my_putstr_error("unsetenv: Too few arguments.\n");
            sk->check_st.is_command_exec = 1;
        }
        if (i >= 2)
            is_in_myenv = exist_in_env(cpy_env, array);
        if (i >= 2 && is_in_myenv == 0) {
            old_env = init_old_env(cpy_env);
            remove_or_change_line(old_env, cpy_env, array);
            free_array(old_env);
        }
    }
}
