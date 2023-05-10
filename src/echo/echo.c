/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** echo
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

static void print_before_variable(char **variable_name)
{
    for (int x = 0; x != len_tab(variable_name) - 1; x++) {
        printf("%s", variable_name[x]);
    }
}

static char *is_a_variable(char *str)
{
    char **variable_name = word_array(str, "$");
    int is_variable = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '$' && i < (my_strlen(str) - 1)) {
            is_variable = 1;
        }
        if (is_variable == 1) {
            print_before_variable(variable_name);
            return variable_name[len_tab(variable_name) - 1];
        }
    }
    return NULL;
}

static void print_message(stock_t *sk, char **cpy_env)
{
    char **quotes = NULL;
    char *variable_name = NULL;

    for (int i = 1; sk->array_st.space[i] != NULL; i += 1) {
        quotes = word_array(sk->array_st.space[i], "\"");
        variable_name = is_a_variable(quotes[0]);
        if (variable_name != NULL) {
            print_variable_value(variable_name, cpy_env);
        } else {
            printf("%s", quotes[0]);
        }
        if (sk->array_st.space[i + 1] != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}

void my_echo(stock_t *sk, char **cpy_env)
{
    int is_echo = my_strcomp("echo", sk->array_st.space[0]);

    if (is_echo == 0) {
        sk->check_st.is_a_builtin = 1;
        if (search_env_variables(sk, cpy_env) == 0) {
            print_message(sk, cpy_env);
        }
    }
}
