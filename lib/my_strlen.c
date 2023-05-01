/*
** EPITECH PROJECT, 2022
** my_strlen.c
** File description:
** count the characters of the string
*/

#include <unistd.h>

int my_strlen(char const *str)
{
    int count = 0;

    while (str[count] != '\0') {
        count++;
    }
    return (count);
}
