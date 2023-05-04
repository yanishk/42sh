/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** count_duck
*/

#include "my.h"

void count_duck(stock_t *sk, int i)
{
    sk->check_st.count_duck = 0;
    sk->check_st. count_reverse_duck = 0;

    for (int j = 0; sk->array_st.virg[i][j]; j += 1) {
        if (sk->array_st.virg[i][j] == '>')
            sk->check_st.count_duck += 1;
        if (sk->array_st.virg[i][j] == '<')
            sk->check_st. count_reverse_duck += 1;
    }
}
