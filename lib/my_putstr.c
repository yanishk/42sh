/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** display the character of a string
*/

#include <unistd.h>

int my_putchar(char c);

int my_putstr(char const *str)
{
    int a = 0;

    while (str[a] != '\0') {
        my_putchar(str[a]);
        a++;
    }
    return (0);
}
