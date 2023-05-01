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
    int my_putchar(char c);
    int my_getnbr(char const *str);
    char *my_strdup(char const *src);
    int my_strlen(char const *str);
    int my_strcomp(char *str, char *comp);
    int my_strcomp_wo_len(char *str, char *comp);
    char* my_strcat (char *dest, char const *src);
    char *my_strcpy(char *dest, char const *src);
    int is_delimiter(char c, char *delim);
    int cut_str(char const *str, char *delim);
    int check_character(char const *str, char *delim, int cut_here);
    char **word_array_delim(char const *str, char *delimiters);
    void print_array(char **array);
    void free_array(char **array);

    void print_prompt(void);
    void get_input(char **env, stock_t *sk, char *path, char ***cpy_env);
    int exit_shell(stock_t *sk);
    int child_process(char** env, char *usr_bin, stock_t *sk);
    char* pars_env(char **cpy_env);
    char* find_dots(char *path, stock_t *sk);
    char* get_path(char *path);
    char* pars_home(char ***cpy_env);
    char* find_equal_cd(char *home);
    void create_cd(char ***cpy_env, stock_t *sk);
    char* find_equal_old(char *old);
    char* pars_old(void);
    void cd_with_arg(stock_t *sk, char *home_path, char *cwd);
    char* remove_path(char *path);
    char*** create_setenv(stock_t *sk, char*** cpy_env);
    int loop_buffer(char **array);
    char** copy_env(char **env);
    int len_line_env(char **env, int x);
    char *if_name_exit(char ***cpy_env, char *add_sv, int x, char *value);
    char** concat(stock_t *sk, int x, char ***cpy_env, char **change_env);
    char** my_setenv(stock_t *sk, char ***cpy_env);
    int len_line_add_sv(char **change_env);
    void check_error(int status, stock_t *sk);
    int error_cd(char **cd, int res, int check);
    int check_both_array(stock_t *sk, int check);
    void if_arraytwo_null(int check, stock_t *sk, char **change_env, int x);
    void new_line_env(int check, stock_t *sk, char **change_env, int x);
    void cpy_struct_env(char **cpy_env, stock_t *sk);
    void cpy_struct_triple(char ***cpy_env, stock_t *sk);
    void create_env(stock_t *sk);
    void which_error(int status, stock_t *sk);
    char** cpy_unset_func(stock_t *sk);
    char** unset_cpy_env(stock_t *sk);
    void unset_env(stock_t *sk);
    char** create_unsetenv(stock_t *sk);
    int check_first_array(stock_t *sk, int check);
    void print_env_setenv(stock_t *sk);
    void redirect_into_file(stock_t *sk, char **env,
    char *path, char ***cpy_env);
    void execute_command_redirect(char **env, char *path,
    char ***cpy_env, stock_t *sk);
    int exec_source_file(char **env, stock_t *sk);
    void count_duck(stock_t *sk);
    void execute_command(char **env, char *path, char ***cpy_env, stock_t *sk);
    int execute_command_pipe(char **env, char *path,
    char ***cpy_env, stock_t *sk);
    int execute_pipe(stock_t *sk, char **env, char *path, char ***cpy_env);

#endif /* !MY_H_ */
