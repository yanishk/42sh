/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** count_duck
*/

#include "my.h"

void count_duck(stock_t *sk)
{
    for (int j = 0; sk->array_virg[sk->index][j]; j += 1) {
        if (sk->array_virg[sk->index][j] == '>')
            sk->count_duck += 1;
    }
}
