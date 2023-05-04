/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** loop_buffer
*/

#include <sys/stat.h>
#include <unistd.h>
#include "my.h"

int loop_buffer(char **array)
{
    struct stat sb;

    if (stat(array[0], &sb) == -1)
        return (0);
    for (int index = 0; array[0][index] != '\0'; index += 1) {
        if (array[0][index] == '/' && ((sb.st_mode & S_IFMT) == S_IFREG)
        && access(array[0], X_OK) == 0) {
            return (1);
        }
        if ((array[0][index] == '/' && access(array[0], X_OK) != 0) ||
            (array[0][index] == '/' && ((sb.st_mode & S_IFMT) != S_IFREG))) {
            my_putstr_error(array[0]);
            my_putstr_error(": Permission denied.\n");
            return (2);
        }
    }
    return (0);
}
