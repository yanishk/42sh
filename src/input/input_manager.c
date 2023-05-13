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
#include <dirent.h>
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

static void handle_tab(stock_t *sk, char **env_cpy)
{
    DIR *tab;
    struct dirent *directory_tab;
    char *current_path = getcwd(NULL, 0);

    tab = opendir(".");
    if (tab == NULL)
        return;
    printf("\n");
    while ((directory_tab = readdir(tab)) != NULL) {
        if (directory_tab->d_name[0] != '.')
            printf("%s\t", directory_tab->d_name);
    }
    printf("\n");
    choice_prompt(sk, current_path, env_cpy);
    closedir(tab);
    return;
}

static void tab_or_no(stock_t *sk, char c, char **env_cpy)
{
    if (c == '\t') {
        c = '\0';
        handle_tab(sk, env_cpy);
    }
}

int input_manager(stock_t *sk, char **env_cpy)
{
    char c = '\0';
    int status = 0;
    char *current_path = getcwd(NULL, 0);
    init_input(sk);

    while (c != '\n') {
        read(STDIN_FILENO, &c, 1);
        if (c == 4) {
            sk->check_st.end = 1;
            return 1;
        }
        tab_or_no(sk, c, env_cpy);
        arrow_check(c, sk);
        remove_input(sk, c);
        if (c != '\033' && c != '[' && c != '\b' && c != 127 && c != '\t')
            status = set_cmd(sk, c);
    }
    if (sk->input.cmd_len == 2)
        choice_prompt(sk, current_path, env_cpy);
    return status;
}
