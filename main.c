/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "my.h"

void control_c(int signal)
{
    if (signal == SIGINT)
        my_putstr("\n$> ");
}

void print_prompt(void)
{
    int check = isatty(STDIN_FILENO);

    if (check == 1)
        my_putstr("$> ");
}

char **set_cpy_env(char **env)
{
    char **cpy_env = NULL;

    if (env[0] != NULL) {
        cpy_env = env;
    } else {
        cpy_env = malloc(sizeof(char *));
        cpy_env[0] = NULL;
    }
    return cpy_env;
}

int main(int ac, char **av, char **env)
{
    if (ac != 1)
        return (84);

    signal(SIGINT, control_c);
    stock_t *sk = malloc(sizeof(stock_t));
    char **cpy_env = set_cpy_env(env);
    char *cwd = pars_env(cpy_env);
    char *path = remove_path(cwd);
    get_input(sk, path, cpy_env);
    return (0);
}
