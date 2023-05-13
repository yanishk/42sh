/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include "my.h"


void control_c(int signal)
{
    if (signal == SIGINT)
        return;
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
    char **cpy_env = set_cpy_env(env);
    char *path = remove_path(cpy_env);
    stock_t *sk = malloc(sizeof(stock_t));
    sk->check_st.size_term = 0;
    sk->check_st.end = 0;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    if (error_handling_help(ac, av) == 84)
        return 84;
    if (help_commad(av) == 1 && ac > 1)
        return 0;
    signal(SIGINT, control_c);
    memset(sk, 0, sizeof(stock_t));
    get_input(sk, path, cpy_env);
    return (sk->check_st.end - 1);
}
