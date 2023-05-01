/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_strcomp
*/

int my_strlen(char const *str);

int my_strcomp_wo_len(char *str, char *comp)
{
    for (int i = 0; comp[i] != '\0'; i += 1) {
        if (str[i] != comp[i])
            return 1;
    }
    return 0;
}
