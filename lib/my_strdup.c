/*
** EPITECH PROJECT, 2022
** my_strdup.c
** File description:
** copy a string & allocates memory
*/

#include <stdlib.h>

int my_strlen(char const *str);

char *my_strdup(char const *src)
{
    char *str;
    int i = 0;

    str = malloc(sizeof(char) * (my_strlen(src) + 1));

    while (src[i] != '\0') {
        str[i] = src[i];
        i++;
    }

    str[i] = '\0';
    return (str);
}
