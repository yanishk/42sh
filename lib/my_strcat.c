/*
** EPITECH PROJECT, 2022
** my_strcat
** File description:
** idk
*/
#include <string.h>

int my_strlen(char const *str);

char* my_strcat (char *dest, char const *src)
{
    int i = 0;
    int len1 = my_strlen(dest);

    while (src[i] != '\0') {
        dest[len1 + i] = src[i];
        i++;
    }
    dest[len1 + i] = '\0';
    return (dest);
}
