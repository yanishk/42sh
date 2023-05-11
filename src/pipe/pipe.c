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

void exec_parent_pro_pipe2(stock_t *sk, char *usr_bin, char *path,
char **cpy_env)
{
    sk->array_st.duck =
    word_array(sk->array_st.pipe[sk->pipe_st.index_pipe], ">");
    sk->array_st.reverse_duck =
    word_array(sk->array_st.pipe[sk->pipe_st.index_pipe], "<");
    usr_bin = find_dots(path, sk, 1);
    if (sk->array_st.duck[1] != NULL) {
        sk->array_st.space = word_array(sk->array_st.duck[0], " \t\n");
        sk->array_st.space_snd = word_array(sk->array_st.duck[1], " \t\n");
        execute_command_redirect_pipe(usr_bin, cpy_env, sk);
    }
    if (sk->array_st.reverse_duck[1] != NULL) {
        sk->array_st.space = word_array(sk->array_st.reverse_duck[0], " \t\n");
        sk->array_st.space_snd =
        word_array(sk->array_st.reverse_duck[1], " \t\n");
        execute_command_reverse_redirect_pipe(usr_bin, cpy_env, sk);
    }
    if (sk->array_st.duck[1] == NULL && sk->array_st.reverse_duck[1] == NULL) {
        int exec = execve(usr_bin, sk->array_st.space, cpy_env);
        error_exec(exec, sk, usr_bin);
    }
}

void exec_parent_pro_pipe(stock_t *sk, char *path, int *fds, char **cpy_env)
{
    char *usr_bin = NULL;

    dup2(sk->pipe_st.input, 0);
    dup2(fds[1], 1);
    close(fds[0]);
    sk->array_st.space =
    word_array(sk->array_st.pipe[sk->pipe_st.index_pipe], " \t\n");
    exec_parent_pro_pipe2(sk, usr_bin, path, cpy_env);
    check_command_found(sk, usr_bin);
}
