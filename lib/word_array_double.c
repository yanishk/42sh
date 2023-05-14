/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** pool day08
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int check_double(char const *str, char c)
{
    int count_words = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        while (i == 0 && str[i] == c && str[i + 1] == c)
            i += 2;
        if (i > 0 && str[i - 1] != c && str[i] == c && str[i + 1] == c) {
            count_words += 1;
        }
    }
    return (count_words);
}

int malloc_array(char const *str, char **array, char c)
{
    int x = 0;
    int number_of_characters = 0;

    for (int i = 0; str[i] != '\0' ; i += 1) {
        while (i == 0 && str[i] == c && str[i + 1] == c)
            i += 2;
        if (i > 0 && str[i - 1] != c && str[i] == c && str[i + 1] == c) {
            array[x] = malloc(sizeof(char) * (number_of_characters + 1));
            number_of_characters = 0;
            x += 1;
        } else {
            number_of_characters += 1;
        }
    }
    array[x] = malloc(sizeof(char) * (number_of_characters + 1));
    return (0);
}

int fill_array(char const *str, char **array, char c)
{
    int x = 0;
    int y = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        while (i == 0 && str[i] == c && str[i + 1] == c)
            i += 2;
        if (i > 0 && str[i - 1] != c && str[i] == c && str[i + 1] == c) {
            array[x][y] = '\0';
            y = 0;
            x += 1;
            i += 1;
        } else {
            array[x][y] = str[i];
            y += 1;
        }
    }
    array[x][y] = '\0';
    array[x + 1] = NULL;
    return (0);
}

char **word_array_double(char const *str, char c)
{
    int number_of_words = check_double(str, c) + 1;
    char **array = malloc(sizeof(char *) * (number_of_words + 1));

    malloc_array(str, array, c);
    fill_array(str, array, c);
    return (array);
}
