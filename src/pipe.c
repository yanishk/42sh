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

int builtin_pipe(char  **cpy_env, stock_t *sk, char **end)
{
    int is_a_source_file = loop_buffer(end);

    if (is_a_source_file == 1) {
        create_cd(cpy_env, sk);
        if (sk->check == 0)
            exec_source_file(cpy_env, sk);
    }
    if (is_a_source_file == 0) {
        create_cd(cpy_env, sk);
        open_history_file(sk);
        history_command(sk);
        my_setenv(cpy_env, sk->array_space, sk);
        my_unsetenv(cpy_env, sk->array_space, sk);
    }
    return is_a_source_file;
}

void error_exec(int exec, stock_t *sk)
{
    if (exec == -1) {
        my_putstr(sk->array_space[0]);
        my_putstr(": Command not found.");
        my_putchar('\n');
        exit(0);
    }
}

void close_fds(int fd_1, stock_t *sk)
{
    if (fd_1 != 1)
        close(fd_1);
    if (sk->input != 0)
        close(sk->input);
}

int execute_pipe(stock_t *sk, char *path, char  **cpy_env)
{
    int status; int exec = 0; int fds[2]; char *usr_bin;

    if (sk->index_pipe < (sk->count_pipe - 1))
        pipe(fds);
    else {
        fds[1] = 1; fds[0] = -1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        dup2(sk->input, 0); dup2(fds[1], 1); close(fds[0]);
        sk->array_space =
        word_array_delim(sk->array_pipe[sk->index_pipe], " \t\n");
        usr_bin = find_dots(path, sk);
        exec = execve(usr_bin, sk->array_space, cpy_env); error_exec(exec, sk);
    } close_fds(fds[1], sk);
    if (sk->index_pipe < (sk->count_pipe - 1)) {
        sk->index_pipe += 1; sk->input = fds[0];
        execute_pipe(sk, path, cpy_env);
    }
    waitpid(pid, &status, 0); return status;
}

int execute_command_pipe(char *path,
char  **cpy_env, stock_t *sk)
{
    int is_a_source_file = 0;
    int status = 0;
    sk->count_pipe = 0;
    sk->index_pipe = 0;
    for (int i = 0; sk->array_pipe[i] != NULL; i += 1) {
        int pipe = my_strcomp_wo_len("|", sk->array_pipe[i]);
        if (pipe == 1)
            sk->count_pipe += 1;
        sk->array_space = word_array_delim(sk->array_pipe[i], " \t\n");
    }
    is_a_source_file = builtin_pipe(cpy_env, sk, sk->array_space);
    sk->input = 0;
    if (sk->check != 1 && is_a_source_file == 0 && exit_shell(sk) == 0) {
        status = execute_pipe(sk, path, cpy_env);
        which_error(status, sk);
    }
    return status;
}
