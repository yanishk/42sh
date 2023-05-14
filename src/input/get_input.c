/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** get_input
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include "my.h"

static char **alias_manager(stock_t *sk, char **tab)
{
    sk->array_st.alias = malloc(sizeof(char *) * (len_tab(tab) + 1));
    int i = 0;
    while (tab[i] != NULL) {
        sk->array_st.alias[i] = malloc(sizeof(char) * (my_strlen(tab[i]) + 1));
        my_strcpy(sk->array_st.alias[i], tab[i]);
        i++;
    }
    sk->array_st.alias[i] = NULL;
    read_alias(sk, 0);
    tab = malloc(sizeof(char *) * (len_tab(sk->array_st.alias) + 1));
    i = 0;
    while (sk->array_st.alias[i] != NULL) {
        tab[i] = malloc(sizeof(char) * (my_strlen(sk->array_st.alias[i]) + 1));
        my_strcpy(tab[i], sk->array_st.alias[i]);
        i++;
    }
    tab[i] = NULL;
    free_array(sk->array_st.alias);
    return tab;
}

void main_exec(stock_t *sk, char *path, char  **cpy_env)
{
    sk->check_st.size_term = get_size_term();
    for (int i = 0; sk->array_st.virg[i] &&
    sk->check_st.is_a_builtin != 84; i += 1) {
        sk->check_st.is_a_command = 1;
        sk->check_st.is_command_exec = 0;
        sk->check_st.is_double_pipe = 0;
        sk->array_st.double_and = word_array(sk->array_st.virg[i], ";&");
        sk->array_st.double_and = alias_manager(sk, sk->array_st.double_and);
        check_command_type(path, cpy_env, sk);
    }
}

static int input_no_term(stock_t *sk, char **cpy_env)
{
    size_t bufsize = 0;
    sk->array_st.buffer = NULL;

    getline(&sk->array_st.buffer, &bufsize, stdin);
    if (my_strlen(sk->array_st.buffer) == 1) {
        print_prompt(sk, getcwd(NULL, 0), cpy_env);
        return 1;
    }
    if (my_strlen(sk->array_st.buffer) < 1) {
        sk->check_st.end = 1;
        return 1;
    }
    return 0;
}

static int input_type(stock_t *sk, char **cpy_env)
{
    int status = 0;
    struct termios orig_termios, new_termios;
    if (isatty(0) == 0)
        return input_no_term(sk, cpy_env);

    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    status = input_manager(sk, cpy_env);
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    return status;
}

void get_input(stock_t *sk, char *path, char  **cpy_env)
{
    int valid = 0;
    sk->array_st.buffer = NULL;
    sk->check_st.number_command = 0;
    sk->check_st.size_term = get_size_term();
    sk->input.nb_key_up = 0;

    choice_prompt(sk, getcwd(NULL, 0), cpy_env);
    while (sk->check_st.end == 0) {
        sk->check_st.size_term = get_size_term();
        valid = input_type(sk, cpy_env);
        if (valid != 0)
            continue;
        sk->check_st.is_a_builtin = 0;
        sk->array_st.virg = word_array(sk->array_st.buffer, ";");
        sk->array_st.virg = alias_manager(sk, sk->array_st.virg);
        main_exec(sk, path, cpy_env);
        if (sk->check_st.end == 0)
            choice_prompt(sk, getcwd(NULL, 0), cpy_env);
    }
}
