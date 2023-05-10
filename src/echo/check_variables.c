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

static char *is_variable(char *str)
{
    char **variable_name = word_array(str, "$");
    int is_variable = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '$' && i < (my_strlen(str) - 1)) {
            is_variable = 1;
        }
        if (is_variable == 1) {
            return variable_name[len_tab(variable_name) - 1];
        }
    }
    return NULL;
}

static int check_existence_in_env(stock_t *sk, char *variable_name,
char **cpy_env)
{
    char **is_variable_name = NULL;

    if (strcmp("?", variable_name) == 0) {
        printf("%d\n", sk->check_st.last_return_value);
        return (1);
    }
    for (int i = 0; cpy_env[i] != NULL; i += 1) {
        is_variable_name = word_array(cpy_env[i], "=");
        if (strcmp(is_variable_name[0], variable_name) == 0) {
            return (0);
        }
    }
    printf("%s: Undefined variable.\n", variable_name);
    sk->check_st.is_command_exec = 1;
    return (1);
}

static int check_variable_name(stock_t *sk, char *variable_name, char **cpy_env)
{
    if (variable_name != NULL) {
        if (check_existence_in_env(sk, variable_name, cpy_env) == 1)
            return (1);
    }
    return (0);
}

int search_env_variables(stock_t *sk, char **cpy_env)
{
    char **quotes = NULL;
    char *variable_name = NULL;

    for (int i = 1; sk->array_st.space[i] != NULL; i += 1) {
        quotes = word_array(sk->array_st.space[i], "\"");
        variable_name = is_variable(quotes[0]);
        if (check_variable_name(sk, variable_name, cpy_env) == 1) {
            return (1);
        }
    }
    return (0);
}
