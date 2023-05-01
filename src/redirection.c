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

void execute_redirect(char **env, char *path, char  **cpy_env, stock_t *sk)
{
    char *usr_bin = NULL;

    if (loop_buffer(sk->array_space) == 1) {
        create_cd(cpy_env, sk);
        if (sk->check == 0)
            exec_source_file(env, sk);
    }
    if (loop_buffer(sk->array_space) == 0 && exit_shell(sk) == 0) {
        usr_bin = find_dots(path, sk);
        create_cd(cpy_env, sk);
        my_setenv(cpy_env, sk->array_space, sk);
        my_unsetenv(cpy_env, sk->array_space, sk);
        if (sk->check == 0)
            child_process(env, usr_bin, sk);
    }
}

void execute_command_redirect(char **env, char *path,
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
    execute_redirect(env, path, cpy_env, sk);
    dup2(out, 1);
}
