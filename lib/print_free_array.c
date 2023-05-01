/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include <stdlib.h>
#include "my.h"

void print_array(char **array)
{
    for (int x = 0; array[x] != NULL; x++) {
        my_putstr(array[x]);
        my_putchar('\n');
    }
}

void free_array(char **array)
{
    for (int x = 0; array[x] != NULL; x++) {
        free(array[x]);
    }
    free(array);
}
