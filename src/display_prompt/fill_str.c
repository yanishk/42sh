/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** fill_str
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* fill_str(char* str, size_t size, char c)
{
    size_t len_str = size + 1;
    str = malloc(len_str * sizeof(char));

    for (size_t i = 0; i < size; i++) {
        str[i] = c;
    }
    str[size] = '\0';
    return str;
}
