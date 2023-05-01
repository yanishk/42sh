/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** set_env
*/

#include <stdlib.h>
#include "my.h"

int check_both_array(stock_t *sk, int check)
{
    if (sk->array_space[1] == NULL) {
        check = 1;
    }
    return check;
}

void if_arraytwo_null(int check, stock_t *sk, char **change_env, int x)
{
    char *add_sv;
    char *name = sk->array_space[1];
    if (check != 1 && sk->array_space[2] == NULL) {
        add_sv = malloc(sizeof(char) * (my_strlen(name) + 2));
        add_sv[0] = '\0';
        my_strcat(add_sv, name);
        change_env[x] = my_strdup(add_sv);
        change_env[x + 1] = NULL;
    }
}

void new_line_env(int check, stock_t *sk, char **change_env, int x)
{
    char *add_sv;
    char *name = sk->array_space[1];
    char *value = sk->array_space[2];

    if (check != 1 && sk->array_space[2] != NULL) {
        add_sv = malloc(sizeof(char) *
            (my_strlen(name) + my_strlen(value) + 2));
        add_sv[0] = '\0';
        my_strcat(add_sv, name);
        my_strcat(add_sv, value);
        change_env[x] = my_strdup(add_sv);
        change_env[x + 1] = NULL;
    }
}

char** realloc_cpy_env(char **change_env, char ***cpy_env)
{
    int x = 0;

    x = len_line_add_sv(change_env);
    *cpy_env = malloc(sizeof(char *) * (x + 1));
    x = 0;
    while (change_env[x] != NULL) {
        (*cpy_env)[x] = my_strdup(change_env[x]);
        x += 1;
    }
    (*cpy_env)[x] = NULL;
    free(change_env);
    return *cpy_env;
}

char*** create_setenv(stock_t *sk, char*** cpy_env)
{
    int res = my_strcomp_wo_len(sk->array_space[0], "setenv");

    if (res == 0) {
        if (sk->array_space[1] == NULL) {
            print_env_setenv(sk);
        sk->check = 1;
        } else {
            sk->check = 1;
            char **change_env = my_setenv(sk, cpy_env);
            *cpy_env = realloc_cpy_env(change_env, cpy_env);
            cpy_struct_triple(cpy_env, sk);
        }
    }
    return cpy_env;
}
