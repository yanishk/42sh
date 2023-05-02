/*
** EPITECH PROJECT, 2023
** coding_style
** File description:
** colorize_str
*/

#include <string.h>
#include <stdlib.h>

char *colorize_str(const char *str, const char *color)
{
    size_t str_len = strlen(str);
    size_t color_len = strlen(color);
    size_t total_len = str_len + color_len + strlen("\033[0m");
    char *colored_str = malloc(total_len + 1);

    if (colored_str == NULL) {
        return NULL;
    }
    strcpy(colored_str, color);
    strcat(colored_str, str);
    strcat(colored_str, "\033[0m");
    return colored_str;
}
