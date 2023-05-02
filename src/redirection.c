/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** redirection
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "my.h"

void execute_command_redirect(char *path,
char  **cpy_env, stock_t *sk)
{
    int fd = 0;
    int out = 0;

    if (sk->count_duck == 1)
        fd = open(sk->array_space_snd[0], O_WRONLY | O_TRUNC | O_CREAT, 422);
    if (sk->count_duck == 2)
        fd = open(sk->array_space_snd[0], O_WRONLY | O_APPEND | O_CREAT, 422);
    out = dup(1);
    dup2(fd, 1);
    execute_command(path, cpy_env, sk);
    dup2(out, 1);
}
