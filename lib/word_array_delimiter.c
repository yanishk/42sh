/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** pool day08
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void word_array1(char const *str, char **array, char *delim, int cut_here)
{
    int i = 0;
    int x = 0;
    int number_of_characters = 0;
    int check2 = 2;

    for (i = 0; str[i] != '\0' ; i++) {
        int check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1
        && i != 0 && i < cut_here) {
            array[x] = malloc(sizeof(char) * (number_of_characters + 1));
            number_of_characters = 0;
            x++;
        }
        if (check1 == 1)
            number_of_characters++;
    }
    array[x] = malloc(sizeof(char) * (number_of_characters + 1));
}

void word_array2(char const *str, char **array, char *delim, int cut_here)
{
    int i = 0;
    int x = 0; int y = 0;
    int check2 = 2;
    for (i = 0; str[i] != '\0'; i++) {
        int check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1
        && i != 0 && i < cut_here) {
            array[x][y] = '\0';
            y = 0;
            x++;
        }
        if (check1 == 1) {
        array[x][y] = str[i];
        y++;
        }
    }
    array[x][y] = '\0';
    array[x + 1] = NULL;
}

char **word_array(char const *str, char *delim)
{
    int cut_here = my_strlen(str);
    int check = is_delimiter(str[my_strlen(str) - 1], delim);
    if (check == 0) {
        cut_here = cut_str(str, delim);
    }
    int number_of_words = check_character(str, delim, cut_here) + 1;

    char **array = malloc(sizeof(char *) * (number_of_words + 1));

    word_array1(str, array, delim, cut_here);
    word_array2(str, array, delim, cut_here);

    return (array);
}
