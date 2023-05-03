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

static int change_cmd(stock_t *sk, char **ligne, int j)
{
    char *new_cmd = malloc(sizeof(char) * 1000);
    for (int k = 1; ligne[j + k] != NULL; k++) {
        if (k > 1)
            my_strcat(new_cmd, " ");
        my_strcat(new_cmd, ligne[j + k]);
    }
    my_strcat(new_cmd, "\n\0");
    strcpy(sk->buffer, new_cmd);
    free(ligne);
    return 0;
}

static int find_alias(stock_t *sk, char **tab, char *cmd)
{
    for (int i = 0; i < len_tab(tab); i++) {
        char **ligne = word_array_delim(tab[i], "'= \t\n");
        int len_ligne = len_tab(ligne);
        int j = 0;
        while (j < len_ligne && strcmp(ligne[j], cmd)) {
            j++;
        }
        if (j != len_ligne && ligne[j + 1] && j == 1) {
            change_cmd(sk, ligne, j);
            free(tab);
            free(cmd);
            return 0;
        }
    }
    free(tab);
    free(cmd);
    return 1;
}

int read_alias(stock_t *sk)
{
    char *buf = open_rc();
    if (buf == NULL)
        return 84;
    char **tab = word_array_delim(buf, "\n");
    char *cmd = strdup(sk->buffer);
    cmd[my_strlen(sk->buffer) - 1] = '\0';
    char **cmd_tab = word_array_delim(cmd, " ");

    if (!strcmp(cmd, "alias")) {
        sk->check = 1;
        print_alias(tab);
    }
    if (!strcmp(cmd_tab[0], "alias") && len_tab(cmd_tab) > 2) {
        sk->check = 1;
        add_alias(cmd_tab);
    }
    if (find_alias(sk, tab, cmd) == 0) {
        read_alias(sk);
    }
    return 0;
}
