/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** print_alias
*/

#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int pass_space(char *str, int i)
{
    while (str[i] != ' ') {
        i++;
    }
    i++;

    return i;
}

void print_alias(char **tab)
{
    int j = 0;
    for (int i = 0; tab[i]; i++) {
        j = pass_space(tab[i], j);
        while (tab[i][j] != '=') {
            my_putchar(tab[i][j]);
            j++;
        }
        while (tab[i][j] == '=' || tab[i][j] == 39) {
            j++;
        }
        my_putstr("\t");
        my_putstr("\033[34m");
        while (tab[i][j] != 39 && tab[i][j] != '\0') {
            my_putchar(tab[i][j]);
            j++;
        }
        my_putstr("\033[0m");
        my_putstr("\n");
        j = 0;
    }
}
