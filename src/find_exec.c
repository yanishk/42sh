/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** find_exec
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "my.h"

static char* concat_malloc_path(stock_t *sk, char **array_path, int x)
{
    int len_array = 0;
    int len_arg = 0;
    char *path_concat = NULL;

    len_array = my_strlen(array_path[x]);
    if (sk->array_space[0] == NULL) {
        my_putstr("Invalid null command.\n");
        return NULL;
    }
    len_arg = my_strlen(sk->array_space[0]);
    path_concat = malloc(sizeof(char) * (len_array + len_arg + 2));
    my_strcpy(path_concat, array_path[x]);
    path_concat = my_strcat(path_concat, "/");
    path_concat = my_strcat(path_concat, sk->array_space[0]);
    return path_concat;
}

char* find_dots(char *path, stock_t *sk)
{
    char **array_path = word_array_delim(path, ":");
    int x = 0;
    char *path_concat = NULL;

    if (path == NULL)
        return NULL;
    array_path = word_array_delim(path, ":");
    while (array_path[x] != NULL) {
        path_concat = concat_malloc_path(sk, array_path, x);
        if (access(path_concat, X_OK) == 0) {
            free(array_path);
            return path_concat;
        }
        x += 1;
        free(path_concat);
    }
    array_path[x] = NULL;
    free(array_path);
    return NULL;
}
