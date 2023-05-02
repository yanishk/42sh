/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** my_str_to_word_array_alias
*/

#include <stddef.h>
#include <stdlib.h>

static int delimiter_alias(char const character)
{
    if (character == 39 || character == '=' ||
    character == ' ' || character == '\n' || character == '\t') {
        return 1;
    } else {
        return 0;
    }
}

static int count_words_alias(char const *str)
{
    int count = 0;
    int var = 0;
    if (str == NULL) {
        return 84;
    }

    while (str[count] != '\0') {
        if ((delimiter_alias(str[count]) == 0
        && delimiter_alias(str[count + 1]) == 1)
        || (delimiter_alias(str[count]) == 0 && str[count + 1] == '\0')) {
            var++;
        }
        count++;
    }
    return (var);
}

static int count_char_alias(char const *str, int index)
{
    int count_char = 0;

    while (str[index] != '\0' && delimiter_alias(str[index]) == 0) {
        count_char += 1;
        index += 1;
    }
    return count_char;
}

char **my_str_to_word_array_alias(char const *str)
{
    int count_chars = 0; int words = count_words_alias(str);
    char **array = malloc(sizeof(char *) * (words + 1));
    int index = 0; int x = 0; int y = 0;

    while (str[index] != '\0') {
        if (delimiter_alias(str[index]) == 1) {
            index += 1;
            continue;
        }
        count_chars = count_char_alias(str, index);
        array[x] = malloc(sizeof(char) * (count_chars + 1)); y = 0;
        while (y < count_chars) {
            array[x][y] = str[index + y]; y += 1;
        }
        array[x][count_chars] = '\0'; x += 1;
        index += count_chars;
    }
    array[x] = NULL; return array;
}
