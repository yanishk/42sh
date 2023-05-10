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
    sk->check_st.is_a_command = 1;
    sk->check_st.is_command_exec = 0;
    sk->check_st.is_double_pipe = 0;
    for (int i = 0; sk->array_st.virg[i] != NULL &&
    sk->check_st.is_a_builtin != 84; i += 1) {
        sk->array_st.pipe = word_array(sk->array_st.virg[i], "|");
        sk->array_st.double_and = word_array(sk->array_st.virg[i], ";&");
        sk->array_st.double_and = alias_manager(sk, sk->array_st.double_and);
        count_duck(sk, i);
        count_pipe(sk, i);
        if (sk->array_st.pipe[1] != NULL && sk->check_st.is_double_pipe == 0)
            execute_command_pipe(path, cpy_env, sk);
        else
            check_command_type(path, cpy_env, sk);
    }
}

void get_input(stock_t *sk, char *path, char  **cpy_env)
{
    int valid = 0;
    sk->array_st.buffer = NULL;
    sk->check_st.number_command = 0;
    sk->input.nb_key_up = 0;
    print_prompt();
    while (sk->check_st.end == 0) {
        valid = input_manager(sk);
        if (valid != 0)
            continue;
        sk->check_st.is_a_builtin = 0;
        sk->array_st.virg = word_array(sk->array_st.buffer, ";");
        sk->array_st.virg = alias_manager(sk, sk->array_st.virg);
        main_exec(sk, path, cpy_env);
        if (sk->check_st.end == 0)
            print_prompt();
    }
}
