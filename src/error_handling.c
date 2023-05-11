/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** error_handling
*/

#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "my.h"

void check_error(int status, stock_t *sk)
{
    sk->check_st.sig = 0;
    sk->check_st.core = 0;

    if (WIFSIGNALED(status)) {
        sk->check_st.sig = WTERMSIG(status);
        if (WCOREDUMP(status)) {
            sk->check_st.core = 1;
        }
    }
}

void which_error(int status, stock_t *sk)
{
    check_error(status, sk);
    if (sk->check_st.sig == SIGSEGV && sk->check_st.core == 1) {
        my_putstr_error("Segmentation fault (core dumped)\n");
    }
    if (sk->check_st.sig == SIGSEGV && sk->check_st.core == 0) {
        my_putstr_error("Segmentation fault\n");
    }
    if (sk->check_st.sig == SIGFPE && sk->check_st.core == 1) {
        my_putstr_error("Floating exception (core dumped)\n");
    }
    if (sk->check_st.sig == SIGFPE && sk->check_st.core == 0) {
        my_putstr_error("Floating exception\n");
    }
    if (sk->check_st.sig == SIGABRT && sk->check_st.core == 0) {
        my_putstr_error("Aborted\n");
    }
    if (sk->check_st.sig == SIGABRT && sk->check_st.core == 1) {
        my_putstr_error("Aborted (core dumped)\n");
    }
}

void check_command(char *usr_bin, char *str, stock_t *sk)
{
    if (sk->check_st.is_a_builtin == 0 && usr_bin == NULL) {
        if (sk->array_st.space[0][0] != '\0' && sk->array_st.space[0] != NULL) {
            my_putstr_error(str);
            my_putstr_error(": Command not found.\n");
        }
        sk->check_st.is_a_command = 0;
        return;
    }
    sk->check_st.is_a_command = 1;
}
