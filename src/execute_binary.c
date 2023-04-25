/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** execute_binary
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "my.h"

int child_process(char** env, char *usr_bin, stock_t *sk)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit (84);
    if (pid == 0) {
        int exec = execve(usr_bin, sk->array_space, env);
        if (exec == -1) {
            my_putstr(sk->array_space[0]);
            my_putstr(": Command not found.");
            my_putchar('\n');
            exit (0);
        }
    } else {
        wait (&status);
    }
    which_error(status, sk);
    return status;
}

int exec_source_file(char **env, stock_t *sk)
{
    char *path;
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit (84);
    if (pid == 0) {
        int exec = execve(sk->array_space[0], sk->array_space, env);
        if (exec == -1) {
            my_putstr(sk->array_space[0]);
            my_putstr(": Command not found.\n");
            exit (84);
        }
    } else {
        wait (&status);
    }
    which_error(status, sk);
    return status;
}

void execute_command(char **env, char *path, char ***cpy_env, stock_t *sk)
{
    char *usr_bin = NULL;

    if (loop_buffer(sk->array_space) == 1) {
        create_cd(cpy_env, sk);
        if (sk->check == 0)
            exec_source_file(env, sk);
    } else {
        exit_sh(sk);
        usr_bin = find_dots(path, sk);
        create_cd(cpy_env, sk);
        cpy_env = create_setenv(env, sk, cpy_env);
        create_unsetenv(sk, env);
        create_env(sk);
        if (sk->check == 0)
            child_process(env, usr_bin, sk);
    }
}
