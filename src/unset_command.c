/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** unset_command
*/

#include "my.h"
#include "stockage.h"

#include <stdlib.h>
#include <signal.h>

char** cpy_unset_func(stock_t *sk)
{
    int x = 0;
    while (sk->print_env[x] != NULL) {
        x += 1;
    }
    char **cpy_unset = malloc(sizeof(char *) * (x + 1));
    x = 0;
    while (sk->print_env[x] != NULL) {
        cpy_unset[x] = my_strdup(sk->print_env[x]);
        x += 1;
    }
    cpy_unset[x] = NULL;
    free(sk->print_env);
    return cpy_unset;
}

char** unset_cpy_env(char **env, stock_t *sk)
{
    char **cpy_unset = cpy_unset_func(sk);
    int index = 0;
    int y = 0;
    char *arg = sk->array_space[1];

    while (cpy_unset[index] != NULL) {
        index += 1;
    }
    char **unset = malloc(sizeof(char*) * index);
    for (int x = 0; cpy_unset[x] != NULL; x += 1) {
        int comp = my_strcomp_wo_len(cpy_unset[x], arg);
        if (comp == 0) {
            x += 1;
        }
        unset[y] = my_strdup(cpy_unset[x]);
        y += 1;
    }
    unset[y] = NULL;
    free(cpy_unset);
    return unset;
}

void unset_env(char **env, stock_t *sk)
{

    char **unset = unset_cpy_env(env, sk);
    int index = 0;

    while (unset[index] != NULL) {
        index += 1;
    }
    sk->print_env = malloc(sizeof(char*) * index + 1);
    for (int x = 0; unset[x] != NULL; x += 1) {
        sk->print_env[x] = my_strdup(unset[x]);
    }
}

char** create_unsetenv(stock_t *sk, char **env)
{
    int res = my_strcomp_wo_len(sk->array_space[0], "unsetenv");
    char **cpy_unset = NULL;
    if (res == 0) {
        sk->check = 1;
        unset_env(env, sk);
    }
    return cpy_unset;
}
