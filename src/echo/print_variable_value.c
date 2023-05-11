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

char *remove_variable_name(char *path)
{
    int i = 0;
    int len = 0;
    int index = 0;
    char *new_path = NULL;

    while (path[i] != '=')
        i += 1;
    i += 1;
    len = my_strlen(path) - i;
    new_path = malloc(sizeof(char) * (len + 1));
    while (path[i] != '\0') {
        new_path[index] = path[i];
        index += 1;
        i += 1;
    }
    new_path[index] = '\0';
    return new_path;
}

void print_variable_value(char *variable_name, char **cpy_env)
{
    char **is_variable_name = NULL;
    char *variable_value = NULL;

    for (int i = 0; cpy_env[i] != NULL; i += 1) {
        is_variable_name = word_array(cpy_env[i], "=");
        if (strcmp(is_variable_name[0], variable_name) == 0 &&
            len_tab(is_variable_name) > 1) {
            variable_value = remove_variable_name(cpy_env[i]);
            printf("%s", variable_value);
        }
    }
}
