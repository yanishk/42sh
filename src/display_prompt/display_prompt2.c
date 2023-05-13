/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** display_prompt
*/

#include <stdio.h>
#include "sys/ioctl.h"
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

static char *colorize_return_value(stock_t *sk, char *return_value, int len)
{
    int len_term = sk->check_st.size_term - len;
    char *str = NULL;

    if (sk->check_st.last_return_value != 0) {
        str = malloc(sizeof(char *) * (len_term + 1));
        return_value = fill_str(return_value, len_term, ' ');
        sprintf(str, "%s%d↲",
        return_value, sk->check_st.last_return_value);
        str = colorize_str(str, "\033[31m");
    }
    if (sk->check_st.last_return_value == 0){
        str = malloc(sizeof(char *) * (len_term + 1));
        return_value = fill_str(return_value, len_term, ' ');
        sprintf(str, "%s%d↲",
        return_value, sk->check_st.last_return_value);
        str = colorize_str(str, "\033[32m");
    }
    return str;
}

static void display_return_values(stock_t *sk, int len)
{
    char *point_value = " ●";
    char *return_value = NULL;

    if (sk->check_st.last_return_value != 0) {
        point_value = colorize_str(point_value, "\033[31m");
        return_value = colorize_return_value(sk, return_value, len);
    }
    if (sk->check_st.last_return_value == 0) {
        point_value = colorize_str(point_value, "\033[32m");
        return_value = colorize_return_value(sk, return_value, len);
    }
    my_putstr(point_value);
    my_putstr(return_value);
}

static void display_line(stock_t *sk, char *logname, char *current_path)
{
    ssize_t len = 0;
    my_putstr("\033[34m┌──(\033[33m");
    my_putstr(logname);
    my_putstr("\033[34m)-[");
    my_putstr(current_path);
    my_putstr("]\033[0m");
    len = strlen(current_path) + strlen(logname) + 14;
    display_return_values(sk, len);
    my_putchar('\n');
    my_putstr("\033[34m└─$ \033[0m");
}

int print_prompt2(stock_t *sk, char *current_path, char **env_cpy)
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
        display_line(sk, logname, current_path);
    return 0;
}
