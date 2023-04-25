/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** main
*/

#include <stdlib.h>
#include <signal.h>

#include "my.h"

void control_c(int signal)
{
    my_putstr("\n$> ");
}

int main(int ac, char **av, char **env)
{
    if (ac != 1)
        exit (84);
    stock_t *sk = malloc(sizeof(stock_t));
    signal(SIGINT, control_c);
    char **cpy_env = copy_env(env);
    cpy_struct_env(cpy_env, sk);
    char *cwd = pars_env(cpy_env);
    char *path = remove_path(cwd);
    get_input(env, sk, path, &cpy_env);
}
