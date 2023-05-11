/*
** EPITECH PROJECT, 2023
** gobling
** File description:
** glob_exe
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <glob.h>

#include "my.h"

static int child_process_glob(char** cpy_env, char *usr_bin,
stock_t *sk, glob_t glob_array)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit(84);
    if (pid == 0) {
        int exec = execve(usr_bin, &glob_array.gl_pathv[0], cpy_env);
        if (exec == -1) {
            my_putstr_error(sk->array_st.space[0]);
            my_putstr_error(": Exec format error. Wrong Architecture.\n");
            exit(0);
        }
    } else {
        wait(&status);
    }
    which_error(status, sk);
    if (status != 0)
        sk->check_st.is_command_exec = 1;
    return status;
}

static int exec_source_file_glob(char **cpy_env, stock_t *sk)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit (84);
    if (pid == 0) {
        int exec = execve(sk->array_st.space[0], sk->array_st.space, cpy_env);
        if (exec == -1) {
            my_putstr_error(sk->array_st.space[0]);
            my_putstr_error(": Exec format error. Wrong Architecture.\n");
            exit(0);
        }
    } else {
        wait(&status);
    }
    which_error(status, sk);
    if (status != 0)
        sk->check_st.is_command_exec = 1;
    return status;
}

static void check_builtins_glob(char **cpy_env, stock_t *sk)
{
    create_cd(cpy_env, sk);
    open_history_file(sk);
    history_command(sk);
    print_env(sk->array_st.space, cpy_env);
    my_setenv(cpy_env, sk->array_st.space, sk);
    my_unsetenv(cpy_env, sk->array_st.space, sk);
    exit_shell(sk);
}

void execute_command_glob(char *path, char  **cpy_env,
stock_t *sk, glob_t glob_array)
{
    char *usr_bin = NULL;
    int is_a_source_file = loop_buffer(sk->array_st.space);

    sk->check_st.is_a_builtin = 0;
    sk->check_st.last_return_value = 1;
    path = remove_path(cpy_env);
    if (is_a_source_file == 1) {
        create_cd(cpy_env, sk);
        if (sk->check_st.is_a_builtin == 0)
            exec_source_file_glob(cpy_env, sk);
    }
    if (is_a_source_file == 0) {
        usr_bin = find_dots(path, sk, 0);
        check_builtins_glob(cpy_env, sk);
        check_command(usr_bin, sk->array_st.space[0], sk);
        if (sk->check_st.is_a_builtin == 0 && sk->check_st.is_a_command == 1)
            child_process_glob(cpy_env, usr_bin, sk, glob_array);
        free(usr_bin);
    }
    actualize_return_value(sk);
}
