/*
** EPITECH PROJECT, 2022
** my_sokoban
** File description:
** my
*/

#include "stockage.h"

#ifndef MY_H_
    #define MY_H_

    int my_putstr(char const *str);
    void my_putstr_error(char *str);
    int my_putchar(char c);
    int my_getnbr(char const *str);
    char *my_strdup(char const *src);
    char *my_strdup_str(char const *src1, char c);
    char *my_strdup_strings(char const *src1, char const *src2, char c);
    int my_strlen(char const *str);
    int my_strcomp(char *str, char *comp);
    int my_strcomp_wo_len(char *str, char *comp);
    void my_swap_str(char **a, char **b);
    char* my_strcat (char *dest, char const *src);
    char *my_strcpy(char *dest, char const *src);
    int is_delimiter(char c, char *delim);
    int cut_str(char const *str, char *delim);
    int check_character(char const *str, char *delim, int cut_here);
    char **word_array_delim(char const *str, char *delimiters);
    void print_array(char **array);
    void free_array(char **array);
    char *my_revstr(char *str);
    char *my_int_to_str(int nb);
    char *colorize_str(const char *str, const char *color);

    void print_prompt(void);
    char **init_old_env(char **my_env);
    void my_setenv(char **my_env, char **array, stock_t *sk);
    void my_unsetenv(char **my_env, char **array, stock_t *sk);
    int setenv_error_handling(char **array, int i);
    void get_input(stock_t *sk, char *path, char  **cpy_env);
    int exit_shell(stock_t *sk);
    int child_process(char** env, char *usr_bin, stock_t *sk);
    char* pars_env(char **cpy_env);
    char* find_dots(char *path, stock_t *sk);
    char* pars_home(char  **cpy_env);
    char* find_equal_cd(char *home);
    void create_cd(char  **cpy_env, stock_t *sk);
    char* pars_old(void);
    void cd_with_arg(stock_t *sk, char *home_path, char *cwd);
    char* remove_path(char *path);
    int loop_buffer(char **array);
    void check_error(int status, stock_t *sk);
    void which_error(int status, stock_t *sk);
    int check_first_array(stock_t *sk, int check);
    void execute_command_redirect(char *path,
    char  **cpy_env, stock_t *sk);
    int exec_source_file(char **env, stock_t *sk);
    void count_duck(stock_t *sk);
    void execute_command(char *path, char  **cpy_env, stock_t *sk);
    int execute_command_pipe(char *path, char  **cpy_env, stock_t *sk);
    int execute_pipe(stock_t *sk, char *path, char  **cpy_env);
    int read_alias(stock_t *sk);
    char **my_str_to_word_array_alias(char const *str);
    char **my_str_to_word_array_delim(char const *str, char delim);
    void print_alias(char **tab);
    void add_alias(char **tab);
    int open_history_file(stock_t *sk);
    int history_command(stock_t *sk);
    int get_last_command_number(stock_t *sk, char *buffer);

    int execute_command_reverse_redirect(char *path,
    char  **cpy_env, stock_t *sk);

#endif /* !MY_H_ */
