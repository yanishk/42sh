/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** arrow_up_down
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

static char *open_history(void)
{
    struct stat sb;
    int type = stat("./.history_log", &sb);
    int fd = open("./.history_log", O_RDONLY);
    if (type == -1 || fd == -1) {
        return NULL;
    }
    char *buf = malloc(sizeof(char) * sb.st_size);

    read(fd, buf, sb.st_size);
    buf[sb.st_size - 1] = '\0';
    close(fd);
    return buf;
}

static void arrow_cmd(stock_t *sk, char *history_ligne)
{
    int i = 0;
    for (int pass = 0; pass < 3; i++) {
        if (history_ligne[i] == ' ')
            pass++;
    }
    char *new_cmd = malloc(sizeof(char) * (strlen(history_ligne) - i + 1));
    for (int j = 0; history_ligne[i - 1] != '\0'; j++, i++) {
        new_cmd[j] = history_ligne[i];
    }
    for (int j = 0; j < sk->input.cmd_len; j++) {
        write(1, "\b \b", 3);
    }
    sk->input.cmd = my_strdup(new_cmd);
    sk->input.cmd_len = my_strlen(sk->input.cmd) + 1;
    write(1, " ", 1);
    write(1, sk->input.cmd, my_strlen(sk->input.cmd));
}

void arrow_up(stock_t *sk)
{
    char *buf = open_history();
    if (buf == NULL || buf[0] == '\0')
        return;
    sk->input.nb_key_up++;
    char **tab = word_array(buf, "\n");
    int len_ligne = len_tab(tab);
    if (len_ligne - sk->input.nb_key_up < 0) {
        sk->input.nb_key_up--;
        return;
    }
    char *history_ligne = tab[len_ligne - sk->input.nb_key_up];
    arrow_cmd(sk, history_ligne);
}

void arrow_down(stock_t *sk)
{
    char *buf = open_history();
    if (buf == NULL || buf[0] == '\0')
        return;
    if (sk->input.nb_key_up <= 0)
        return;
    if (sk->input.nb_key_up == 1) {
        char *tmp = "\0";
        for (int j = 0; j < sk->input.cmd_len - 1; j++) {
            write(1, "\b \b", 3);
        }
        sk->input.cmd = strdup(tmp);
        sk->input.cmd_len = 1;
        sk->input.nb_key_up = 0;
        return;
    }
    sk->input.nb_key_up--;
    char **tab = word_array(buf, "\n");
    int len_ligne = len_tab(tab);
    char *history_ligne = tab[len_ligne - sk->input.nb_key_up];
    arrow_cmd(sk, history_ligne);
}
