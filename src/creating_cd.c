/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** creating_exec
*/

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "my.h"

char* pars_home(char  **cpy_env)
{
    int i = 0;
    char *home;
    int res;

    if (cpy_env[0] == NULL)
        return NULL;
    while (cpy_env[i]) {
        res = my_strcomp_wo_len(cpy_env[i], "HOME=");
        if (res == 0)
            home = cpy_env[i];
        i += 1;
    }
    return home;
}

char* find_equal_cd(char *home)
{
    int i = 0;
    int index = 0;
    int index2 = 0;

    if (home != NULL) {
        while (home[i] != '=')
            i += 1;
        i += 1;
        index2 = i;
        while (home[index2] != '\0')
            index2 += 1;
        char *home_path = malloc(sizeof(char) * (index2 + 1));
        for (; home[i] != '\0'; i += 1) {
            home_path[index] = home[i];
            index += 1;
        }
        home_path[index] = '\0';
        return home_path;
    }
    return NULL;
}

int check_error_cd(int stat_re, struct stat info_file, stock_t *sk, int check)
{
    if (sk->array_st.space[1] != NULL && sk->array_st.space[2] != NULL) {
        my_putstr_error("cd: Too many arguments.\n");
        check = 1; return check;
    }
    if (stat_re == -1
    && sk->array_st.space[1][0] != '~' && sk->array_st.space[1][0] != '-') {
        my_putstr_error(sk->array_st.space[1]);
        my_putstr_error(": No such file or directory.\n");
        check = 1; return check;
    }
    if (sk->array_st.space[1][0] != '~' && sk->array_st.space[1][0] != '-') {
        int res = chdir(sk->array_st.space[1]);
        if ((info_file.st_mode & S_IFMT) != S_IFDIR && res == -1
            && sk->array_st.space[1] != NULL && check != 1) {
            my_putstr_error(sk->array_st.space[1]);
            my_putstr_error(": Not a directory.\n");
            check = 1; return check;
        }
    }
    return check;
}

void cd_with_arg(stock_t *sk, char *home_path, char *old_path)
{
    struct stat info_file;
    int stat_re = stat(sk->array_st.space[1], &info_file);
    int check = 0;

    check = check_error_cd(stat_re, info_file, sk, check);

    if (check == 1)
        sk->check_st.is_command_exec = 1;
    if (sk->array_st.space[1][0] == '~')
        chdir(home_path);
    if (sk->array_st.space[1][0] == '-')
        chdir(old_path);
}

void create_cd(char  **cpy_env, stock_t *sk)
{
    struct stat info_file;
    static char *cwd = NULL;
    static char *old_path = NULL;
    int res = my_strcomp_wo_len(sk->array_st.space[0], "cd");

    cwd = pars_old();
    if (res == 0) {
        sk->check_st.is_a_builtin = 1;
        stat(sk->array_st.space[1], &info_file);
        char *home = pars_home(cpy_env);
        char *home_path = find_equal_cd(home);
        if (sk->array_st.space[1] == NULL) {
            chdir(home_path);
        } else {
            cd_with_arg(sk, home_path, old_path);
        }
        old_path = malloc(sizeof(char) * my_strlen(cwd + 1));
        old_path = cwd;
    }
}
