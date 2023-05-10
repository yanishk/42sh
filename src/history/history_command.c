/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** history_command
*/

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include "my.h"

char *copy_content_file(char *file)
{
    struct stat sb;
    int fd = 0;
    char *buffer = NULL;

    if (stat(file, &sb) == -1)
        return NULL;
    buffer = malloc((sizeof(char)) * (sb.st_size + 1));
    if (buffer == NULL) {
        return NULL;
    }
    fd = open(file, O_RDONLY);
    if (fd < 0) {
        return NULL;
    }
    if (read(fd, buffer, sb.st_size) == -1)
        return NULL;
    buffer[sb.st_size] = '\0';
    if (close(fd) == -1)
        return NULL;
    return buffer;
}

static int print_array_history(char **array, int i)
{
    char **tab = NULL;
    int z = 0;

    tab = word_array(array[i], " ");
    if (tab == NULL)
        return 84;
    while (tab[z] != NULL) {
        if (z == 1 || z == 2) {
            tab[z] = colorize_str(tab[z], "\033[34m");
            printf("%s ", tab[z]);
        } else {
            printf("%s ", tab[z]);
        }
        z += 1;
    }
    return 0;
}

static int history_command_loop(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        if (print_array_history(array, i) == 84)
            return 84;
        printf("\n");
        i += 1;
    }
    return 0;
}

int history_command(stock_t *sk)
{
    char *buffer = NULL;
    char **array = NULL;

    buffer = copy_content_file(".history_log");
    if (buffer == NULL)
        return 84;
    array = word_array(buffer, "\n");
    if (array == NULL)
        return 84;
    if (my_strcomp(sk->array_st.buffer, "history\n") == 0) {
        sk->check_st.is_a_builtin = 1;
        if (history_command_loop(array) == 84)
            return 84;
    }
    return 0;
}
