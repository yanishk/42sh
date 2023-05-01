/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** split string into words
*/

#include <stdlib.h>
#include <stdio.h>

int delimiter_two(char const character)
{
    if (character == ':') {
        return 1;
    } else {
        return 0;
    }
}

int count_words_two(char const *str)
{
    int count = 0;
    int var = 0;
    if (str == NULL) {
        return 84;
    }
    while (str[count] != '\0') {
        if ((delimiter_two(str[count]) == 0
        && delimiter_two(str[count + 1]) == 1)
        || (delimiter_two(str[count]) == 0 && str[count + 1] == '\0')) {
            var++;
        }
        count++;
    }
    return (var);
}

int count_char_two(char const *str, int index)
{
    int count_char = 0;

    while (str[index] != '\0' && delimiter_two(str[index]) == 0) {
        count_char += 1;
        index += 1;
    }
    return count_char;
}

char **word_array_two_dots(char const *str)
{
    int count_chars = 0; int words = count_words_two(str);
    char **array = malloc(sizeof(char *) * (words + 1));
    int index = 0; int x = 0; int y = 0;

    while (str[index] != '\0') {
        if (delimiter_two(str[index]) == 1) {
            index += 1;
            continue;
        }
        count_chars = count_char_two(str, index);
        array[x] = malloc(sizeof(char) * (count_chars + 1)); y = 0;
        while (y < count_chars) {
            array[x][y] = str[index + y]; y += 1;
        }
        array[x][count_chars] = '\0';
        x += 1; index += count_chars;
    }
    array[x] = NULL;
    return array;
}
