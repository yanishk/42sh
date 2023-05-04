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
    sk->sig = 0;
    sk->core = 0;

    if (WIFSIGNALED(status)) {
        sk->sig = WTERMSIG(status);
        if (WCOREDUMP(status)) {
            sk->core = 1;
        }
    }
}

void which_error(int status, stock_t *sk)
{
    check_error(status, sk);
    if (sk->sig == SIGSEGV && sk->core == 1) {
        my_putstr_error("Segmentation fault (core dumped)\n");
    }
    if (sk->sig == SIGSEGV && sk->core == 0) {
        my_putstr_error("Segmentation fault\n");
    }
    if (sk->sig == SIGFPE && sk->core == 1) {
        my_putstr_error("Floating exception (core dumped)\n");
    }
    if (sk->sig == SIGFPE && sk->core == 0) {
        my_putstr_error("Floating exception\n");
    }
    if (sk->sig == SIGABRT && sk->core == 0) {
        my_putstr_error("Aborted\n");
    }
    if (sk->sig == SIGABRT && sk->core == 1) {
        my_putstr_error("Aborted (core dumped)\n");
    }
}

void check_command(char *usr_bin, char *str, stock_t *sk)
{
    if (sk->is_a_builtin == 0 && usr_bin == NULL) {
        my_putstr_error(str);
        my_putstr_error(": Command not found.\n");
        sk->is_a_command = 0;
        return;
    }
    sk->is_a_command = 1;
}
