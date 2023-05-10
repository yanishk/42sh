/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** add_alias
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my.h"

void add_alias(char **tab)
{
    int fd = open("./.42shrc", O_WRONLY | O_APPEND | O_CREAT, 422);
    write(fd, "\nalias ", 7);
    write(fd, tab[1], my_strlen(tab[1]));
    write(fd, "='", 2);
    for (int i = 2; i < len_tab(tab); i++) {
        write(fd, tab[i], my_strlen(tab[i]));
        if (i < len_tab(tab) - 1) {
            write(fd, " ", 1);
        }
    }
    write(fd, "'", 1);
}
