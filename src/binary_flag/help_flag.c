/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** help_flag
*/

#include "my.h"
#include <stdio.h>

int help_flag(void)
{
    char *help = "my_sh, version 5.2.15(1)-release\n"
    "Usage:  bash [GNU option]\n"
    "GNU options:\n"
    "--help\n--list\n--list-op\n";
    char *str =
    "You can run my_sh without option for use it\n";

    printf("%s", help);
    str = colorize_str(str, "\033[31m");
    printf("%s", str);
    return 0;
}
