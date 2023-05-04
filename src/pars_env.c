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
    if (sk->array_st.space[2] != NULL) {
        if (sk->array_st.space[3] != NULL) {
            my_putstr_error("setenv: Too many arguments.\n");
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
    if ((sk->array_st.space[1][0] < 'A' || sk->array_st.space[1][0] > 'Z')
        && (sk->array_st.space[1][0] < 'a' || sk->array_st.space[1][0] > 'z')) {
        my_putstr_error("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    for (int i = 1; sk->array_st.space[1][i] != '\0'; i += 1) {
        if ((sk->array_st.space[1][i] < 48 || sk->array_st.space[1][i] > 57)
            && (sk->array_st.space[1][i] < 'A' ||
            sk->array_st.space[1][0] > 'Z')
            && (sk->array_st.space[1][0] < 'a' ||
            sk->array_st.space[1][0] > 'z')) {
            my_putstr_error("setenv: Variable name must contain ");
            my_putstr_error("alphanumeric characters.\n");
            return 1;
        }
    }
    return check;
}

char* pars_env(char **cpy_env)
{
    int res = 0;
    char *path;

    if (cpy_env[0] == NULL)
        return NULL;
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
    int len = 0;
    char *new_path = NULL;
    int index = 0;

    if (path != NULL) {
        len = my_strlen(path);
        new_path = malloc(sizeof(char) * (len + 1));
        index = 0;
        while (i != 5)
            i += 1;
        while (path[i] != '\0') {
            new_path[index] = path[i];
            index += 1;
            i += 1;
        }
            new_path[index] = '\0';
            return new_path;
    }
    return NULL;
}
