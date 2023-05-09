/*
** EPITECH PROJECT, 2022
** stock
** File description:
** stock\
*/

#ifndef STOCK_H_
    #define STOCK_H_

typedef struct pipe_s {
    int count_pipe;
    int index_pipe;
    int input;
} pipe_t;

typedef struct array_s {
    char *buffer;
    char **virg;
    char **space;
    char **space_snd;
    char **duck;
    char **reverse_duck;
    char **pipe;
    char **double_and;
    char **double_pipe;
    char **alias;
} array_t;

typedef struct check_s {
    int is_a_builtin;
    int is_a_command;
    int is_command_exec;
    int is_double_pipe;
    int count_duck;
    int count_reverse_duck;
    int count_ast;
    int number_command;
    int sig;
    int core;
} check_t;

typedef struct stock_s {
    pipe_t pipe_st;
    array_t array_st;
    check_t check_st;
} stock_t;

#endif
