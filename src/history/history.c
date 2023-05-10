/*
** EPITECH PROJECT, 2023
** coding_style
** File description:
** history
*/

#include "my.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int write_command(stock_t *sk, int fd)
{
    char *cmd_str = NULL;

    cmd_str = strdup(sk->array_st.buffer);
    if (cmd_str == NULL)
        return 84;
    if (write(fd, cmd_str, strlen(cmd_str)) == -1) {
        free(cmd_str);
        return 84;
    }
    return 0;
}

static int write_number_of_command(stock_t *sk, int fd)
{
    char *str_nb_command = NULL;

    sk->check_st.number_command += 1;
    str_nb_command = my_int_to_str(sk->check_st.number_command);
    if (str_nb_command == NULL)
        return 84;
    if (write(fd, str_nb_command, strlen(str_nb_command)) == -1)
        return 84;
    return 0;
}

static int write_time_informations(int fd)
{
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    char date_str[100];

    sprintf(date_str, " %d-%02d-%02d %02d:%02d:%02d ",
            time.tm_year + 1900, time.tm_mon + 1, time.tm_mday,
            time.tm_hour, time.tm_min, time.tm_sec);
    if (write(fd, date_str, strlen(date_str)) == -1) {
        return 84;
    }
    return 0;
}

static int write_in_history_file(stock_t *sk, int fd)
{
    if (write_number_of_command(sk, fd) == 84)
        return 84;
    if (write_time_informations(fd) == 84)
        return 84;
    if (write_command(sk, fd) == 84)
        return 84;
    return 0;
}

int open_history_file(stock_t *sk)
{
    struct stat sb;
    int fd = 0;
    char *buffer = NULL;

    fd = open(".history_log", O_RDWR | O_APPEND | O_CREAT, 0644);
    if (stat(".history_log", &sb) == -1)
        return 84;
    if (fd == -1)
        return 84;
    buffer = malloc((sizeof(char)) * (sb.st_size + 1));
    if (read(fd, buffer, sb.st_size) == -1)
        return 84;
    buffer[sb.st_size] = '\0';
    get_last_command_number(sk, buffer);
    if (write_in_history_file(sk, fd) == 84)
        return 84;
    if (close(fd) == -1)
        return 84;
    return 0;
}
