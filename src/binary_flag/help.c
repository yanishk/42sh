/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** help
*/


#include <stdio.h>
#include <unistd.h>
#include "my.h"

int flag_selection(char * const * av)
{
    for (int i = 0; av[i] != NULL; i++) {
        if (my_strcomp(av[i], "--list") == 0)
            list_flag();
        if (my_strcomp(av[i], "--list-op") == 0)
            list_op_flag();
        if (my_strcomp(av[i], "--help") == 0)
            help_flag();
    }
    return 0;
}

int help_commad(int ac, char * const *av)
{
    if (ac > 2) {
        printf("use --help or --list for more help !");
        return 1;
    } else {
        flag_selection(av);
        return 1;
    }
    return 0;
}
