/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** exec_pipe
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "my.h"

void error_exec(int exec, stock_t *sk, char *usr_bin)
{
    if (exec == -1 && usr_bin != NULL) {
        my_putstr_error(sk->array_st.space[0]);
        my_putstr_error(": Exec format error. Wrong Architecture.\n");
        exit(0);
    }
}

int execute_pipe(stock_t *sk, char *path, char  **cpy_env)
{
    int status = 0;
    int fds[2];

    if (sk->pipe_st.index_pipe < (sk->pipe_st.count_pipe - 1))
        pipe(fds);
    else {
        fds[1] = 1;
        fds[0] = -1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        exec_parent_pro_pipe(sk, path, fds, cpy_env);
    }
    close_fds(fds[1], sk);
    if (sk->pipe_st.index_pipe < (sk->pipe_st.count_pipe - 1)) {
        sk->pipe_st.index_pipe += 1; sk->pipe_st.input = fds[0];
        execute_pipe(sk, path, cpy_env);
    }
    waitpid(pid, &status, 0);
    return status;
}

int execute_command_pipe(char *path, char **cpy_env, stock_t *sk)
{
    int is_a_source_file = 0;
    int status = 0;
    sk->pipe_st.count_pipe = 0;
    sk->pipe_st.index_pipe = 0;

    for (int i = 0; sk->array_st.pipe[i] != NULL; i += 1) {
        int pipe = my_strcomp_wo_len("|", sk->array_st.pipe[i]);
        if (pipe == 1)
            sk->pipe_st.count_pipe += 1;
        sk->array_st.space = word_array(sk->array_st.pipe[i], " \t\n");
    }
    path = remove_path(cpy_env);
    is_a_source_file = builtin_pipe(cpy_env, sk, sk->array_st.space);
    sk->pipe_st.input = 0;
    if (sk->check_st.is_a_builtin == 0 && is_a_source_file == 0) {
        status = execute_pipe(sk, path, cpy_env);
        which_error(status, sk);
    }
    return status;
}
