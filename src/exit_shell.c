/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** get_input
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int is_a_number(stock_t *sk, int x)
{
    for (int y = 0; sk->array_st.space[x][y] != '\0'; y++) {
        if (sk->array_st.space[x][y] < '0' || sk->array_st.space[x][y] > '9')
            return (1);
    }
    return (0);
}

static void exit_simple(stock_t *sk)
{
    sk->check_st.end = 1;
    sk->check_st.is_a_builtin = 1;
}

void exit_shell(stock_t *sk)
{
    int is_exit = my_strcomp("exit", sk->array_st.space[0]);
    int x = 0;
    int nb = 0;

    while (sk->array_st.space[x] != NULL) {
        x += 1;
    }
    if (is_exit == 0 && x == 1) {
        exit_simple(sk);
        return;
    }
    if (is_exit == 0 && x == 2 && is_a_number(sk, (x - 1)) == 0) {
        nb = my_getnbr(sk->array_st.space[1]);
        sk->check_st.end = nb + 1;
        sk->check_st.is_a_builtin = 1;
    } else if (is_exit == 0) {
        write(2, "exit: Expression Syntax.\n", 26);
        sk->check_st.is_a_builtin = 1;
    }
}
