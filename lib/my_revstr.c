/*
** EPITECH PROJECT, 2023
** coding_style
** File description:
** my_rev_str
*/

#include "my.h"

char *my_revstr(char *str)
{
    char temp;
    int length = my_strlen(str) - 1;

    for (int i = 0; i < length; i++) {
        temp = str[i];
        str[i] = str[length];
        str[length] = temp;
        length--;
    }
    return (str);
}
