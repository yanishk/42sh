/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** help
*/


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "my.h"

int error_handling_help(int ac, char **av)
{
    if (ac != 1 && ac != 2) {
        printf("use --help more help !");
        return 84;
    }
    if (ac == 2 && ((strcmp(av[1], "--help") != 0
        && strcmp(av[1], "--list") != 0)
        && strcmp(av[1], "--list-op") != 0)) {
        printf("use --help for more help !");
        return 84;
    }
    if (ac > 2)
        printf("use --help for more help !");
    return 0;
}

static int flag_selection(char * const * av)
{
    for (int i = 0; av[i] != NULL; i++) {
        if (my_strcomp(av[i], "--list") == 0) {
            list_flag();
            return 1;
        }
        if (my_strcomp(av[i], "--list-op") == 0) {
            list_op_flag();
            return 1;
        }
        if (my_strcomp(av[i], "--help") == 0) {
            help_flag();
            return 1;
        }
    }
    return 0;
}

int help_commad(char * const *av)
{
    if (flag_selection(av) == 1)
        return 1;
    return 0;
}
