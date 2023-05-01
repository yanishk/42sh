/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_strcomp
*/

int my_strlen(char const *str);

int my_strcomp(char *str, char *comp)
{
    int len1 = my_strlen(str);
    int len2 = my_strlen(comp);

    if (len1 != len2)
        return 1;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] != comp[i])
            return 1;
    }
    return 0;
}
