/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** pars_env
*/

#include <stdlib.h>
#include <unistd.h>

#include "my.h"

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

char* remove_path(char **cpy_env)
{
    int i = 5;
    int len = 0;
    int index = 0;
    char *path = pars_env(cpy_env);
    char *new_path = NULL;

    if (path != NULL) {
        len = my_strlen(path);
        new_path = malloc(sizeof(char) * (len + 1));
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
