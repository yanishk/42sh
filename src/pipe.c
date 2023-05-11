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

int builtin_pipe(char **cpy_env, stock_t *sk, char **end)
{
    int is_a_source_file = loop_buffer(end);

    if (is_a_source_file == 1) {
        create_cd(cpy_env, sk);
        if (sk->check_st.is_a_builtin == 0)
            exec_source_file(cpy_env, sk);
    }
    if (is_a_source_file == 0) {
        create_cd(cpy_env, sk);
        open_history_file(sk);
        history_command(sk);
        print_env(sk->array_st.space, cpy_env);
        my_setenv(cpy_env, sk->array_st.space, sk);
        my_unsetenv(cpy_env, sk->array_st.space, sk);
        exit_shell(sk);
    }
    actualize_return_value(sk);
    return is_a_source_file;
}

void error_exec(int exec, stock_t *sk, char *usr_bin)
{
    if (exec == -1 && usr_bin != NULL) {
        my_putstr_error(sk->array_st.space[0]);
        my_putstr_error(": Exec format error. Wrong Architecture.\n");
        exit(0);
    }
}

void close_fds(int fd_1, stock_t *sk)
{
    if (fd_1 != 1)
        close(fd_1);
    if (sk->pipe_st.input != 0)
        close(sk->pipe_st.input);
}

void check_command_found(stock_t *sk, char *usr_bin)
{
    if (usr_bin == NULL && sk->array_st.space[0] != NULL) {
        if (sk->array_st.space[0][0] != '\0') {
            dprintf(2, "%s: Command not found.\n", sk->array_st.space[0]);
        } else {
            dprintf(2, "Invalid null command.\n");
        }
        exit(0);
    }
}

char* exec_parent_pro_pipe(stock_t *sk, char *path, int *fds)
{
    char *usr_bin = NULL;

    dup2(sk->pipe_st.input, 0); dup2(fds[1], 1); close(fds[0]);
    sk->array_st.space =
    word_array(sk->array_st.pipe[sk->pipe_st.index_pipe], " \t\n");
    usr_bin = find_dots(path, sk, 1);
    check_command_found(sk, usr_bin);
    return usr_bin;
}
