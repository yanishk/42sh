/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** pipe
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "my.h"

void builtin_pipe(char **env, char ***cpy_env, stock_t *sk, char **end)
{
    if (loop_buffer(end) == 1) {
        create_cd(cpy_env, sk);
        if (sk->check == 0)
            exec_source_file(env, sk);
    } else {
        exit_sh(sk);
        create_cd(cpy_env, sk);
        cpy_env = create_setenv(env, sk, cpy_env);
        create_unsetenv(sk, env);
        create_env(sk);
    }
}

void error_exec(int exec, stock_t *sk)
{
    if (exec == -1) {
        my_putstr(sk->array_space[0]);
        my_putstr(": Command not found.");
        my_putchar('\n');
        exit (0);
    }
}

void close_fds(int fd_1, stock_t *sk)
{
    if (fd_1 != 1)
        close(fd_1);
    if (sk->input != 0)
        close(sk->input);
}

int execute_pipe(stock_t *sk, char **env, char *path, char ***cpy_env)
{
    int status; int exec = 0;
    int fds[2]; char *usr_bin;

    if (sk->index_pipe < (sk->count_pipe - 1))
        pipe(fds);
    else {
        fds[1] = 1; fds[0] = -1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        dup2(sk->input, 0); dup2(fds[1], 1); close(fds[0]);
        sk->array_space = my_str_to_word_array(sk->array_pipe[sk->index_pipe]);
        usr_bin = find_dots(path, sk);
        exec = execve(usr_bin, sk->array_space, env); error_exec(exec, sk);
    } close_fds(fds[1], sk);
    if (sk->index_pipe < (sk->count_pipe - 1)) {
        sk->index_pipe += 1; sk->input = fds[0];
        execute_pipe(sk, env, path, cpy_env);
    }
    waitpid(pid, &status, 0); return status;
}

int execute_command_pipe(char **env, char *path,
char ***cpy_env, stock_t *sk)
{
    int status = 0;
    sk->count_pipe = 0;
    char *usr_bin;
    sk->index_pipe = 0;
    for (int i = 0; sk->array_pipe[i] != NULL; i += 1) {
        int pipe = my_strcomp_wo_len("|", sk->array_pipe[i]);
        if (pipe == 1)
            sk->count_pipe += 1;
            sk->array_space = my_str_to_word_array(sk->array_pipe[i]);
    }
    builtin_pipe(env, cpy_env, sk, sk->array_space);
    sk->input = 0;
    if (sk->check != 1) {
        status = execute_pipe(sk, env, path, cpy_env);
        which_error(status, sk);
    }
    return status;
}
