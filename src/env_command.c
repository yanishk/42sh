/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env_command
*/
#include <stdlib.h>
#include "my.h"
#include "stockage.h"

void cpy_struct_env(char **cpy_env, stock_t *sk)
{
    int index = 0;
    int x = 0;

    while (cpy_env[index] != NULL) {
        index += 1;
    }
    sk->print_env = malloc(sizeof(char *) * (index + 1));
    while ( cpy_env[x] != NULL) {
        sk->print_env[x] = my_strdup(cpy_env[x]);
        x += 1;
    }
    sk->print_env[x] = NULL;
}

void cpy_struct_triple(char ***cpy_env, stock_t *sk)
{
    int index = 0;
    int x = 0;

    while ((*cpy_env)[index] != NULL) {
        index += 1;
    }
    sk->print_env = malloc(sizeof(char *) * (index + 1));
    while ((*cpy_env)[x] != NULL) {
        sk->print_env[x] = my_strdup((*cpy_env)[x]);
        x += 1;
    }
    sk->print_env[x] = NULL;
}

void print_env_setenv(stock_t *sk)
{
    for (int index = 0; sk->print_env[index] != NULL; index += 1) {
        my_putstr(sk->print_env[index]);
        my_putchar('\n');
    }
}

void create_env(stock_t *sk)
{
    int res = my_strcomp_wo_len(sk->buffer, "env");

    if (res == 0) {
        sk->check = 1;
        for (int index = 0; sk->print_env[index] != NULL; index += 1) {
            my_putstr(sk->print_env[index]);
            my_putchar('\n');
        }
    }
}
