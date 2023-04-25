/*
** EPITECH PROJECT, 2022
** my_putchar
** File description:
** print char
*/
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
