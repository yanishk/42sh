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
        my_putstr("Segmentation fault (core dumped)\n");
    }
    if (sk->sig == SIGSEGV && sk->core == 0) {
        my_putstr("Segmentation fault\n");
    }
    if (sk->sig == SIGFPE && sk->core == 1) {
        my_putstr("Floating exception (core dumped)\n");
    }
    if (sk->sig == SIGFPE && sk->core == 0) {
        my_putstr("Floating exception\n");
    }
    if (sk->sig == SIGABRT && sk->core == 0) {
        my_putstr("Aborted\n");
    }
    if (sk->sig == SIGABRT && sk->core == 1) {
        my_putstr("Aborted (core dumped)\n");
    }
}
