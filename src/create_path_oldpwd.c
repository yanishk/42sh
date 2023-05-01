/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** creating_exec
*/

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>

#include "my.h"

char* pars_old(void)
{
    char *cwd = malloc(sizeof(char) * PATH_MAX);
    if (getcwd(cwd, PATH_MAX) == NULL) {
    }
    return cwd;
}
