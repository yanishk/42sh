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
#include <signal.h>

#include "my.h"

int child_process(char** cpy_env, char *usr_bin, stock_t *sk)
{
    pid_t pid = fork();
    int status = 0;
    int exec = 0;

    if (pid == -1)
        exit(84);
    if (pid == 0) {
        exec = execve(usr_bin, sk->array_st.space, cpy_env);
        if (exec == -1) {
            my_putstr_error(sk->array_st.space[0]);
            my_putstr_error(": Exec format error. Wrong Architecture.\n");
            exit(0);
        }
    } else {
        wait(&status);
    }
    which_error(status, sk);
    if (status != 0 || exec == -1)
        sk->check_st.is_command_exec = 1;
    return status;
}

int exec_source_file(char **cpy_env, stock_t *sk)
{
    pid_t pid = fork();
    int status = 0;
    int exec = 0;

    if (pid == -1)
        exit (84);
    if (pid == 0) {
        exec = execve(sk->array_st.space[0], sk->array_st.space, cpy_env);
        if (exec == -1) {
            my_putstr_error(sk->array_st.space[0]);
            my_putstr_error(": Exec format error. Wrong Architecture.\n");
            exit(0);
        }
    } else {
        wait(&status);
    }
    which_error(status, sk);
    if (status != 0 || exec == -1)
        sk->check_st.is_command_exec = 1;
    return status;
}

void check_builtins(char **cpy_env, stock_t *sk)
{
    my_echo(sk, cpy_env);
    create_cd(cpy_env, sk);
    open_history_file(sk);
    history_command(sk);
    print_env(sk->array_st.space, cpy_env);
    my_setenv(cpy_env, sk->array_st.space, sk);
    my_unsetenv(cpy_env, sk->array_st.space, sk);
    exit_shell(sk);
}

void actualize_return_value(stock_t *sk)
{
    if (last_command_succeed(sk)) {
        sk->check_st.last_return_value = 0;
    } else {
        sk->check_st.last_return_value = 1;
    }
    if (sk->check_st.sig == SIGSEGV)
    sk->check_st.last_return_value = 139;
    if (sk->check_st.sig == SIGFPE)
        sk->check_st.last_return_value = 136;
}

void execute_command(char *path, char  **cpy_env, stock_t *sk)
{
    char *usr_bin = NULL;
    int is_a_source_file = loop_buffer(sk->array_st.space);

    sk->check_st.is_a_builtin = 0;
    path = remove_path(cpy_env);
    if (is_a_source_file == 1) {
        create_cd(cpy_env, sk);
        if (sk->check_st.is_a_builtin == 0)
            exec_source_file(cpy_env, sk);
    }
    if (is_a_source_file == 0) {
        usr_bin = find_dots(path, sk, 0);
        check_builtins(cpy_env, sk);
        check_command(usr_bin, sk->array_st.space[0], sk);
        if (sk->check_st.is_a_builtin == 0 && sk->check_st.is_a_command == 1)
            child_process(cpy_env, usr_bin, sk);
        free(usr_bin);
    }
    actualize_return_value(sk);
}
