/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_str_to_word_array
*/

#include <stddef.h>
#include <stdlib.h>

int delimiter(char const character)
{
    if (character == ' ' || character == '\n' || character == '\t') {
        return 1;
    } else {
        return 0;
    }
}

int count_words(char const *str)
{
    int count = 0;
    int var = 0;
    int count_char = 0;
    if (str == NULL) {
        return 84;
    }

    while (str[count] != '\0') {
        if (delimiter(str[count]) == 0 && delimiter(str[count + 1]) == 1
        || delimiter(str[count]) == 0 && str[count + 1] == '\0') {
            var++;
        }
        count++;
    }
    return (var);
}

int count_char(char const *str, int index)
{
    int count_char = 0;

    while (str[index] != '\0' && delimiter(str[index]) == 0) {
        count_char += 1;
        index += 1;
    }
    return count_char;
}

char **my_str_to_word_array(char const *str)
{
    int count_chars = 0; int words = count_words(str);
    char **array = malloc(sizeof(char *) * (words + 1));
    int index = 0; int x = 0; int y = 0;

    while (str[index] != '\0') {
        if (delimiter(str[index]) == 1) {
            index += 1;
            continue;
        }
        count_chars = count_char(str, index);
        array[x] = malloc(sizeof(char) * (count_chars + 1)); y = 0;
        while (y < count_chars) {
            array[x][y] = str[index + y]; y += 1;
        }
        array[x][count_chars] = '\0'; x += 1;
        index += count_chars;
    }
    array[x] = NULL; return array;
}
