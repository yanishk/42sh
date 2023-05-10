/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** change_cmd
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

static int change_cmd(stock_t *sk, char **ligne, int j, int index)
{
    char *new_cmd = '\0';
    int len = 0;
    for (int k = 1; ligne[j + k] != NULL; k++) {
        if (k > 1)
            len += 1;
        len += strlen(ligne[j + k]);
    }
    new_cmd = malloc(sizeof(char) * (len + 2));
    memset(new_cmd, 0, sizeof(char) * (len + 2));
    for (int k = 1; ligne[j + k] != NULL && new_cmd != NULL; k++) {
        if (k > 1)
            my_strcat(new_cmd, " ");
        my_strcat(new_cmd, ligne[j + k]);
    }
    sk->array_st.alias[index] = my_strdup(new_cmd);
    return 0;
}

int find_alias(stock_t *sk, char **tab, char *cmd, int index)
{
    char **ligne = NULL;
    char **ligne2 = NULL;
    for (int i = 0; i < len_tab(tab); i++) {
        ligne = word_array(tab[i], "' =\t\n");
        ligne2 = word_array(tab[i], "' \t\n");
        int len_ligne = len_tab(ligne);
        int j = 0;
        while (j < len_ligne && strcmp(ligne[j], cmd)) {
            j++;
        }
        if (j != len_ligne && ligne[j + 1] != NULL && j == 1) {
            change_cmd(sk, ligne2, j, index);
            read_alias(sk, 0);
        }
    }
    return 1;
}
