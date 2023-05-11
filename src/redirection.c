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
#include <string.h>

#include "my.h"

void execute_command_redirect(char *path, char  **cpy_env, stock_t *sk)
{
    int fd = 0;
    int out = 0;

    if (sk->check_st.count_duck == 1)
        fd = open(sk->array_st.space_snd[0],
        O_WRONLY | O_TRUNC | O_CREAT, 422);
    if (sk->check_st.count_duck == 2)
        fd = open(sk->array_st.space_snd[0],
        O_WRONLY | O_APPEND | O_CREAT, 422);
    out = dup(1);
    dup2(fd, 1);
    execute_command(path, cpy_env, sk);
    dup2(out, 1);
}

int create_file_double(stock_t *sk)
{
    int fd = 0;
    size_t len = 0;
    char *str = NULL;

    fd = open(".temp.txt", O_RDWR | O_TRUNC | O_CREAT, 422);
    if (fd == -1) {
        my_putstr_error("NOPE\n");
        return 84;
    }
    while (getline(&str, &len, stdin) != -1) {
        len = strlen(str);
        str[len - 1] = '\0';
        if (strcmp(str, sk->array_st.space_snd[0]) == 0)
            break;
        write(fd, str, len);
        write(fd, "\n", strlen("\n"));
    }
    close(fd);
    return 0;
}

int send_file_to_exe(char *path, char  **cpy_env, stock_t *sk)
{
    int fd = 0;
    int in = 0;

    if (sk->check_st. count_reverse_duck == 1)
        fd = open(sk->array_st.space_snd[0], O_RDONLY);
    if (sk->check_st. count_reverse_duck == 2)
        fd = open(".temp.txt", O_RDONLY);
    if (fd == -1) {
        my_putstr_error(sk->array_st.space_snd[0]);
        my_putstr_error(": No such file or directory.\n");
        return 84;
    }
    in = dup(0);
    dup2(fd, STDIN_FILENO);
    close(fd);
    execute_command(path, cpy_env, sk);
    dup2(in, 0);
    return 0;
}

int execute_command_reverse_redirect(char *path, char  **cpy_env, stock_t *sk)
{

    if (sk->check_st. count_reverse_duck == 1) {
        send_file_to_exe(path, cpy_env, sk);
    }
    if (sk->check_st. count_reverse_duck == 2) {
        if (create_file_double(sk) == 84)
            return 84;
        send_file_to_exe(path, cpy_env, sk);
    }
    return 0;
}
