/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** get_input
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include "my.h"

bool last_command_succeed(stock_t *sk)
{
    if ((sk->check_st.is_a_command == 1 &&
        sk->check_st.is_command_exec == 0) ||
        (sk->check_st.is_a_builtin == 1 &&
        sk->check_st.is_command_exec == 0)) {
            return true;
        }
    return false;
}

bool last_command_failed(stock_t *sk)
{
    if (((sk->check_st.is_a_command == 1 &&
        sk->check_st.is_command_exec == 1)) ||
        (sk->check_st.is_a_builtin == 1 &&
        sk->check_st.is_command_exec == 1) ||
        (sk->check_st.is_a_command == 0 &&
        sk->check_st.is_a_builtin == 0)) {
            sk->check_st.is_command_exec = 0;
            return true;
        }
    return false;
}
