/*
** EPITECH PROJECT, 2022
** my_strdup.c
** File description:
** pool day08
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    char *str = NULL;
    int i = 0;
    int y = my_strlen(src);

    str = malloc(sizeof(char) * (y + 1));
    while (i < y) {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char *my_strdup_str(char const *src1, char c)
{
    char *str = NULL;
    int i = 0;
    int len = my_strlen(src1);

    str = malloc(sizeof(char) * (len + 2));
    while (len > i) {
        str[i] = src1[i];
        i += 1;
    }
    str[i] = c;
    i += 1;
    str[i] = '\0';
    return (str);
}

char *my_strdup_strings(char const *src1, char const *src2, char c)
{
    char *str = NULL;
    int i = 0;
    int y = 0;
    int len1 = my_strlen(src1);
    int len2 = my_strlen(src2);

    str = malloc(sizeof(char) * (len1 + len2 + 2));
    while (len1 > i) {
        str[i] = src1[i];
        i += 1;
    }
    str[i] = c;
    i += 1;
    while (len2 > y) {
        str[i] = src2[y];
        y += 1;
        i += 1;
    }
    str[i] = '\0';
    return (str);
}
