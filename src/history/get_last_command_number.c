/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** get_last_number_history
*/

#include <unistd.h>
#include "my.h"

int get_last_command_number(stock_t *sk, char *buffer)
{
    char **array = NULL;
    char **tab = NULL;
    int nb_command = 0;

    array = word_array(buffer, "\n");
    for (int i = 0; array[i] != NULL; i++) {
        tab = word_array(array[i], " ");
        nb_command = my_getnbr(tab[0]);
        sk->check_st.number_command = nb_command;
    }
    return 0;
}
