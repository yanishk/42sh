/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** pars_env
*/

#include <stdlib.h>
#include <unistd.h>

#include "my.h"


int check_nb_arg(stock_t *sk, int check)
{
    if (sk->array_space[2] != NULL) {
        if (sk->array_space[3] != NULL) {
            my_putstr("setenv: Too many arguments.\n");
            check = 1;
            return check;
        }
    }
    return check;
}

int check_first_array(stock_t *sk, int check)
{
    check = check_nb_arg(sk, check);
    if (check != 0)
        return check;
    if (sk->array_space[1][0] < 'A' || sk->array_space[1][0] > 'Z'
        && sk->array_space[1][0] < 'a' || sk->array_space[1][0] > 'z') {
        my_putstr("setenv: Variable name must begin with a letter.\n");
        check = 1;
        return check;
    }
    for (int i = 1; sk->array_space[1][i] != '\0'; i += 1) {
        if (sk->array_space[1][i] < 48 || sk->array_space[1][i] > 57
            && sk->array_space[1][i] < 'A' || sk->array_space[1][0] > 'Z'
            && sk->array_space[1][0] < 'a' || sk->array_space[1][0] > 'z') {
            my_putstr("setenv: Variable name must contain ");
            my_putstr("alphanumeric characters.\n");
            check = 1;
            return check;
        }
    }
    return check;
}

char* pars_env(char **cpy_env)
{
    int res = 0;
    char *path;
    if (cpy_env[0] == NULL) {
        return NULL;
    }
    for (int i = 0; cpy_env[i]; i += 1) {
        res = my_strcomp_wo_len(cpy_env[i], "PATH=");
        if (res == 0) {
            path = cpy_env[i];
            return path;
        }
    }
    return NULL;
}

char* remove_path(char *path)
{
    int i = 0;
    if (path != NULL) {
    int len = my_strlen(path);
    char *new_path = malloc(sizeof(char) * (len + 1));
    int index = 0;

    while (i != 5) {
        i += 1;
    }
    while (path[i] != '\0') {
        new_path[index] = path[i];
        index += 1;
        i += 1;
    }
    new_path[index] = '\0';
    return new_path;
    }
}

char* find_dots(char *path, stock_t *sk)
{
    if (path == NULL)
        return NULL;
    char **array_path = word_array_two_dots(path);
    char *path_concat = NULL; int x = 0; int res = 0;
    while (array_path[x] != NULL) {
        int len_array = my_strlen(array_path[x]);
        if (sk->array_space[0] == NULL) {
            my_putstr("Invalid null command.\n"); return NULL;
        }
        int len_arg = my_strlen(sk->array_space[0]);
        path_concat = malloc(sizeof(char) * (len_array + len_arg + 2));
        my_strcpy(path_concat, array_path[x]);
        path_concat = my_strcat(path_concat, "/");
        path_concat = my_strcat(path_concat, sk->array_space[0]);
        if (access(path_concat, X_OK) == 0) {
            free(array_path); return path_concat;
        }
        x += 1; free(path_concat);
    }
    array_path[x] = NULL; free(array_path);
}
