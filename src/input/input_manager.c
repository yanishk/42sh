/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** input_manager
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include "my.h"

static int set_cmd(stock_t *sk, char c)
{
    sk->input.cmd = realloc(sk->input.cmd,
    sk->input.cmd_len + sizeof(char));
    sk->input.cmd[sk->input.cmd_len - 1] = c;
    sk->input.cmd[sk->input.cmd_len] = '\0';
    sk->input.cmd_len++;

    write(1, &c, 1);
    if (c == '\n') {
        sk->input.nb_key_up = 0;
        sk->array_st.buffer = strdup(sk->input.cmd);
        if (strlen(sk->array_st.buffer) <= 1) {
            return 84;
        }
        free(sk->input.cmd);
    }
    return 0;
}

static void remove_input(stock_t *sk, char c)
{
    if (c == '\b' || c == 127) {
        if (sk->input.cmd_len > 1) {
            write(1, "\b \b", 3);
            sk->input.cmd_len--;
            sk->input.cmd[sk->input.cmd_len] = '\0';
        }
    }
}

int input_manager(stock_t *sk)
{
    char c = '\0';
    int status = 0;
    sk->input.cmd = malloc(sizeof(char));
    sk->input.cmd[0] = '\0';
    sk->array_st.buffer = NULL;
    sk->input.cmd_len = 1;
    while (c != '\n') {
        read(STDIN_FILENO, &c, 1);
        if (c == 4) {
            sk->check_st.end = 1;
            return 1;
        }
        arrow_check(c, sk);
        remove_input(sk, c);
        if (c != '\033' && c != '[' && c != '\b' && c != 127) {
            status = set_cmd(sk, c);
        }
    }
    return status;
}
