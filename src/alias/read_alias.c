/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** read_alias
*/

#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char *open_rc(void)
{
    struct stat sb;
    int type = stat("./.42shrc", &sb);
    int fd = open("./.42shrc", O_RDONLY);
    if (type == -1 || fd == -1) {
        open("./.42shrc", O_WRONLY | O_TRUNC | O_CREAT, 422);
        return NULL;
    }
    char *buf = malloc(sizeof(char) * sb.st_size + 10);
    read(fd, buf, sb.st_size);
    buf[sb.st_size] = '\0';
    close(fd);
    return buf;
}

static int len_tab(char **tab)
{
    int len = 0;
    while (tab[len] != NULL) {
        len++;
    }
    return len;
}

static int redirection_alias(stock_t *sk, char **cmd_tab, char **tab, int pass)
{
    if (!strcmp(cmd_tab[0], "alias") && pass == 0 && len_tab(cmd_tab) < 2) {
        print_alias(tab);
        sk->is_a_builtin = 1;
        free_array(tab);
        return 1;
    } else if (!strcmp(cmd_tab[0], "alias") && len_tab(cmd_tab) > 2) {
        add_alias(cmd_tab);
        sk->is_a_builtin = 1;
        free_array(tab);
        return 1;
    }
    if (!strcmp(cmd_tab[0], "alias")) {
        sk->is_a_builtin = 1;
        free_array(tab);
        return 1;
    }

    return 0;
}

int read_alias(stock_t *sk)
{
    char *buf = open_rc();
    int pass = 0;
    char **tab;
    char *cmd = strdup(sk->buffer);
    cmd[my_strlen(sk->buffer) - 1] = '\0';
    char **cmd_tab = word_array_delim(cmd, " ");

    if (buf == NULL || buf[0] == '\0')
        pass = 1;
    else
        tab = word_array_delim(buf, "\n");

    if (redirection_alias(sk, cmd_tab, tab, pass) == 1)
        pass = 1;
    if (pass == 0 && sk->is_a_builtin == 0)
        find_alias(sk, tab, cmd);
    free_array(cmd_tab);
    free(buf);
    return 0;
}
