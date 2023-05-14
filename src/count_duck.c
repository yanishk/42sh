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
    sk->check_st.count_reverse_duck = 0;

    for (int j = 0; sk->array_st.double_and[i][j]; j += 1) {
        if (sk->array_st.double_and[i][j] == '>')
            sk->check_st.count_duck += 1;
        if (sk->array_st.double_and[i][j] == '<')
            sk->check_st.count_reverse_duck += 1;
    }
}

void count_pipe(stock_t *sk, int i)
{
    sk->check_st.is_double_pipe = 0;

    for (int j = 0; sk->array_st.double_and[i][j + 1]; j += 1) {
        if (sk->array_st.double_and[i][j] == '|'
        && sk->array_st.double_and[i][j + 1] == '|')
            sk->check_st.is_double_pipe += 1;
    }
}

void count_asteriks(stock_t *sk, int i)
{
    sk->check_st.count_ast = 0;

    for (int j = 0; sk->array_st.double_and[i][j]; j += 1) {
        if (sk->array_st.double_and[i][j] == '*')
            sk->check_st.count_ast += 1;
    }
}
