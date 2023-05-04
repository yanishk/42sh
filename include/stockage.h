/*
** EPITECH PROJECT, 2022
** stock
** File description:
** stock\
*/

#ifndef STOCK_H_
    #define STOCK_H_

typedef struct stock {
    char **print_env;
    int is_a_builtin;
    int is_a_command;
    int is_command_executed;
    char *buffer;
    int sig;
    int core;
    char **array_virg;
    char **array_space;
    char **array_space_snd;
    char **array_duck;
    char **array_reverse_duck;
    char **array_pipe;
    int count_duck;
    int count_reverse_duck;
    int index;
    int fd[2];
    int old_fd;
    int check_pipe;
    int count_pipe;
    int index_pipe;
    int input;
    int number_command;
} stock_t;

#endif
