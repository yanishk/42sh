/*
** EPITECH PROJECT, 2023
** repo_perso_backup
** File description:
** print_env
*/

#include <stdlib.h>
#include "my.h"

void print_env(char **args, char **env)
{
    if (my_strcomp(args[0], "env") == 0) {
        for (int i = 0; env[i] != NULL; i++) {
            my_putstr(env[i]);
            my_putchar('\n');
        }
    }
}
