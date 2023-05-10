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
    if (signal == SIGQUIT) {
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
    char **cpy_env = set_cpy_env(env);
    char *path = remove_path(cpy_env);
    stock_t *sk = malloc(sizeof(stock_t));
    sk->check_st.end = 0;
    sk->input.is_term = isatty(0);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    if (help_commad(ac, av) == 1 && ac > 1)
        return 0;
    signal(SIGINT, control_c);
    signal(SIGQUIT, control_c);
    memset(sk, 0, sizeof(stock_t));
    get_input(sk, path, cpy_env);
    return (sk->check_st.end - 1);
}
