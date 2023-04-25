/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** loop_buffer
*/

#include "my.h"

int loop_buffer(char **array)
{
    for (int index = 0; array[0][index] != '\0'; index += 1) {
        if (array[0][index] == '/') {
            return 1;
        }
    }
    return 0;
}
