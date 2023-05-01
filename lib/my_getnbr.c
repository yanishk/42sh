/*
** EPITECH PROJECT, 2022
** my_getnbr.c
** File description:
** pool
*/

#include "my.h"

int my_getnbr(char const *str)
{
    int i = 0;
    int nb = 0;
    int nb_length = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            nb = nb * 10 + (str[i] - '0');
            nb_length += 1;
        }
        if (!(str[i] >= '0' && str[i] <= '9') && (nb_length > 0)) {
            break;
        }
        i++;
    }

    return (nb);
}
