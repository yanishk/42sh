/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** display_prompt
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

static char *get_env_value(char *search_variable, char **cpy_env)
{
    char **is_variable_name = NULL;
    char *variable_value = NULL;
    char *variable_name;

    for (int i = 0; cpy_env[i] != NULL; i += 1) {
        is_variable_name = word_array(cpy_env[i], "=");
        if (strcmp(is_variable_name[0], search_variable) == 0 &&
            len_tab(is_variable_name) > 1) {
            variable_value = remove_variable_name(cpy_env[i]);
            variable_name = malloc(sizeof(char) * (strlen(variable_value) + 1));
            sprintf(variable_name, "%s", variable_value);
            return variable_name;
        }
    }
    return NULL;
}

static void display_line(char *logname, char *current_path,
    char *point_value, char *return_value)
{
    my_putstr("\033[34m┌──(\033[33m");
    my_putstr(logname);
    my_putstr("\033[34m)-[");
    my_putstr(current_path);
    my_putstr("]\033[0m");
    my_putstr(point_value);
    my_putstr(return_value);
    my_putchar('\n');
    my_putstr("\033[34m└─$ \033[0m");
}

static char *colorize_return_value(stock_t *sk, char *return_value)
{
    if (sk->check_st.last_return_value != 0) {
        return_value = malloc(sizeof(char) * (35));
        sprintf(return_value, "                            %d ↲",
        sk->check_st.last_return_value);
        return_value = colorize_str(return_value, "\033[31m");
    }
    if (sk->check_st.last_return_value == 0){
        return_value = malloc(sizeof(char) * (35));
        sprintf(return_value, "                            %d ↲",
        sk->check_st.last_return_value);
        return_value = colorize_str(return_value, "\033[32m");
    }
    return return_value;
}

static int get_element_color(stock_t *sk, char *logname, char *current_path)
{
    char *point_value = " ●";
    char *return_value = NULL;

    if (sk->check_st.last_return_value != 0) {
        point_value = colorize_str(point_value, "\033[31m");
        return_value = colorize_return_value(sk, return_value);
    }
    if (sk->check_st.last_return_value == 0) {
        point_value = colorize_str(point_value, "\033[32m");
        return_value = colorize_return_value(sk, return_value);
    }
    display_line(logname, current_path, point_value, return_value);
    return 0;
}

int print_prompt(stock_t *sk, char *current_path, char **env_cpy)
{
    int check = isatty(STDIN_FILENO);
    char *marvin = "marvin㉿";
    int env_i = 0;
    char *logname = get_env_value("USER", env_cpy);

    if (logname == NULL) {
        logname = strdup(marvin);
        env_i = 1;
    }
    if (env_i == 1)
        logname = colorize_str(logname, "\033[31m");
    if (check == 1)
        get_element_color(sk, logname, current_path);
    return 0;
}
