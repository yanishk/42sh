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

static char* concat_malloc_path(stock_t *sk, char **array_path,
int x, int check)
{
    int len_array = 0;
    int len_arg = 0;
    char *path_concat = NULL;

    len_array = my_strlen(array_path[x]);
    if (sk->array_st.space[0] == NULL && check == 1) {
        my_putstr_error("Invalid null command.\n");
        return NULL;
    }
    if (sk->array_st.space[0][0] == '\0') {
        return NULL;
    }
    len_arg = my_strlen(sk->array_st.space[0]);
    path_concat = malloc(sizeof(char) * (len_array + len_arg + 2));
    my_strcpy(path_concat, array_path[x]);
    path_concat = my_strcat(path_concat, "/");
    path_concat = my_strcat(path_concat, sk->array_st.space[0]);
    return path_concat;
}

char* find_dots(char *path, stock_t *sk, int check)
{
    char **array_path = NULL;
    char *path_concat = NULL;
    int x = 0;
    if (path == NULL)
        return NULL;
    array_path = word_array(path, ":");
    while (array_path[x] != NULL) {
        path_concat = concat_malloc_path(sk, array_path, x, check);
        if (path_concat == NULL)
            return NULL;
        if (access(path_concat, X_OK) == 0) {
            free_array(array_path);
            return path_concat;
        }
        x += 1;
        free(path_concat);
    }
    array_path[x] = NULL;
    free_array(array_path);
    return NULL;
}
