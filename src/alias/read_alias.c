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
        fd = open("./.42shrc", O_WRONLY | O_TRUNC | O_CREAT, 422);
        dprintf(fd, "alias ls='ls --color=auto'");
        type = stat("./.42shrc", &sb);
    }
    char *buf = malloc(sizeof(char) * sb.st_size + 10);
    read(fd, buf, sb.st_size);
    buf[sb.st_size] = '\0';
    close(fd);
    return buf;
}

static int redirection_alias(stock_t *sk, char **cmd_tab, char **tab)
{
    if (!strcmp(cmd_tab[0], "alias") && len_tab(cmd_tab) < 2) {
        print_alias(tab);
        sk->check_st.is_a_builtin = 84;
        return 1;
    } else if (!strcmp(cmd_tab[0], "alias") && len_tab(cmd_tab) > 2) {
        add_alias(cmd_tab);
        sk->check_st.is_a_builtin = 84;
        return 1;
    }
    if (!strcmp(cmd_tab[0], "alias")) {
        sk->check_st.is_a_builtin = 84;
        return 1;
    }

    return 0;
}

static char *creat_cmd(stock_t *sk, int index)
{
    if (sk->array_st.alias[index][0] == '\n') {
        sk->array_st.alias[index] = NULL;
        return NULL;
    }
    char *cmd = my_strdup(sk->array_st.alias[index]);
    if (cmd[my_strlen(cmd) - 1] == ' ' || cmd[my_strlen(cmd) - 1] == '\n')
        cmd[my_strlen(cmd) - 1] = '\0';
    for (size_t i = 0; i < strlen(cmd) && cmd[i] == ' '; i++) {
        for (size_t j = 0; j < strlen(cmd); j++) {
            cmd[j] = cmd[j + 1];
        }
    }

    return cmd;
}

char **read_alias(stock_t *sk, int i)
{
    char *buf = open_rc();
    char *cmd = creat_cmd(sk, i);
    if (cmd == NULL) {
        return sk->array_st.alias;
    }
    char **cmd_tab = word_array(cmd, "; ");

    if (buf == NULL || buf[0] == '\0') {
        int fd = open("./.42shrc", O_RDONLY);
        fd = open("./.42shrc", O_WRONLY | O_TRUNC | O_CREAT, 422);
        dprintf(fd, "alias ls='ls --color=auto'");
        close(fd);
        return NULL;
    }
    char **tab = word_array(buf, "\n");
    if (redirection_alias(sk, cmd_tab, tab) == 0)
        find_alias(sk, tab, cmd, i);
    if (i < len_tab(sk->array_st.alias) - 1)
        read_alias(sk, i + 1);
    return sk->array_st.alias;
}
