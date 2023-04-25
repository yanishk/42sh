/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env
*/

#include <stdlib.h>
#include "my.h"

char** copy_env(char **env)
{
    int x = 0; int y = 0;
    while (env[x] != NULL) {
        x += 1;
    }
    char **cpy_env = malloc(sizeof(char *) * (x + 1));
    x = 0;
    while (env[x] != NULL) {
        cpy_env[x] = my_strdup(env[x]);
        x += 1;
    }
    cpy_env[x] = NULL;
    return cpy_env;
}

char *if_name_exit(char ***cpy_env, char *add_sv, int x, char *value)
{
    int index = 0;
    int equal = 0;
    int len_value = my_strlen(value);
    while ((*cpy_env)[x][index] != '=') {
        index += 1;
    }
    index += 1;
    equal = index;
    add_sv = malloc(sizeof(char) * (index + len_value + 2));
    index = 0;
    for (int y = 0; (*cpy_env)[x][y] != '='; y += 1) {
        add_sv[index] = (*cpy_env)[x][y];
        index += 1;
    }
    my_strcat(add_sv, "=");
    my_strcat(add_sv, value);
    return add_sv;
}

char** concat(stock_t *sk, int x, char ***cpy_env, char **change_env)
{
    char *add_sv = NULL; int index = 0; int check = 0;
    char *name = sk->array_space[1];
    char *value = sk->array_space[2];
    check = check_both_array(sk, check);
    check = check_first_array(sk, check);
    name = my_strcat(name, "=");


    for (int x = 0; (*cpy_env)[x] != NULL; x += 1) {
        if (check != 1 && (my_strcomp_wo_len((*cpy_env)[x], name) == 0)) {
                check = 1;
                add_sv = if_name_exit(cpy_env, add_sv, x, value);
                change_env[x] = my_strdup(add_sv);
        }
    }
    new_line_env(check, sk, change_env, x);
    if_arraytwo_null(check, sk, change_env, x);
    free(add_sv);
    return change_env;
}

char** my_setenv(char **env, stock_t *sk, char ***cpy_env)
{
    int x = 0;
    while ((*cpy_env)[x] != NULL) {
        x += 1;
    }
    char **change_env = malloc(sizeof(char *) * (x + 2));
    x = 0;
    while ((*cpy_env)[x] != NULL) {
        change_env[x] = my_strdup((*cpy_env)[x]);
        x += 1;
    }
    change_env = concat(sk, x, cpy_env, change_env);
    free(*cpy_env);
    return change_env;
}

int len_line_add_sv(char **change_env)
{
    int x = 0;

    while (change_env[x] != NULL) {
        x += 1;
    }
    return x;
}
