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
#include "my.h"

/* ORIGINAL FUNC NE PAS RM SVP!!!
void display_line_shell(void)
{
    char *usr_path = "USER=";
    char *log_name = get_env_line_path(env, log_name, usr_path);
    my_putstr("\033[34m┌──(\033[31m");
    my_putstr(log_name);
    my_putstr("㉿\033[34m)-[");
    my_putstr(current_path);
    my_putstr("]\033[0m");
    my_putchar('\n');
    my_putstr("\033[34m└─$ \033[0m");
}
*/

void control_c(int signal)
{
    if (signal == SIGINT) {
        my_putchar('\n');
        print_prompt();
    }
}

void print_prompt(void)
{
    int check = isatty(STDIN_FILENO);

    if (check == 1) {
        my_putstr("\033[34m┌──(\033[31m");
        my_putstr("㉿\033[34m)-[");
        my_putstr("]\033[0m");
        my_putchar('\n');
        my_putstr("\033[34m└─$ \033[0m");
    }
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
    signal(SIGINT, control_c);
    stock_t *sk = malloc(sizeof(stock_t));
    memset(sk, 0, sizeof(stock_t));
    char **cpy_env = set_cpy_env(env);
    char *cwd = pars_env(cpy_env);
    char *path = remove_path(cwd);
    if (help_commad(ac, av) == 1 && ac > 1)
        return 0;
    get_input(sk, cwd, path, cpy_env);
    free(sk);
    free(path);
    return (0);
}
