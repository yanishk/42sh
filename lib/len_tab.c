/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** len_tab
*/

#include <unistd.h>

int len_tab(char **tab)
{
    int len = 0;

    while (tab[len] != NULL) {
        len++;
    }
    return len;
}
