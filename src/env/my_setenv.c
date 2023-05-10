/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "my.h"

char **init_old_env(char **cpy_env)
{
    char **old_env = NULL;
    int nb_of_lines = 0;

    for (nb_of_lines = 0; cpy_env[nb_of_lines] != NULL; nb_of_lines++) {
    }
    old_env = malloc(sizeof(char *) * (nb_of_lines + 1));
    for (int i = 0; i < nb_of_lines; i++) {
        old_env[i] = my_strdup(cpy_env[i]);
    }
    old_env[nb_of_lines] = NULL;
    return old_env;
}

void change_line(char **cpy_env, char **array, int nb_of_lines, int i)
{
    if (i == 2)
        cpy_env[nb_of_lines] = my_strdup_str(array[1], '=');
    if (i == 3)
        cpy_env[nb_of_lines] = my_strdup_strings(array[1], array[2], '=');
}

void add_or_change_line(char **old_env, char **cpy_env, char **array)
{
    char *line = NULL;
    int nb_of_lines = 0;
    int i = 0;
    int line_exist = 1;

    for (nb_of_lines = 0; old_env[nb_of_lines] != NULL; nb_of_lines++) {}
    for (int i = 0; i < nb_of_lines; i++)
        cpy_env[i] = my_strdup(old_env[i]);
    for (i = 0; array[i] != NULL; i++) {}
    line = my_strdup_str(array[1], '=');
    for (nb_of_lines = 0; old_env[nb_of_lines] != NULL; nb_of_lines++) {
        line_exist = my_strcomp_wo_len(old_env[nb_of_lines], line);
        if (line_exist == 0) {
            change_line(cpy_env, array, nb_of_lines, i);
            return;
        }
    }
    change_line(cpy_env, array, nb_of_lines, i);
    cpy_env[nb_of_lines + 1] = NULL;
}

void my_setenv(char **cpy_env, char **array, stock_t *sk)
{
    char **old_env = NULL;
    int is_setenv = my_strcomp("setenv", array[0]);
    int i = 0;

    for (i = 0; array[i] != NULL; i++) {
    }
    if (is_setenv == 0) {
        sk->check_st.is_a_builtin = 1;
        if (setenv_error_handling(array, i) != 0) {
            sk->check_st.is_command_exec = 1;
            return;
        }
        if (i >= 2) {
            old_env = init_old_env(cpy_env);
            add_or_change_line(old_env, cpy_env, array);
            free_array(old_env);
            return;
        }
        print_array(cpy_env);
    }
}
