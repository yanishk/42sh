/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** list_flag
*/

#include <unistd.h>
#include "my.h"
#include <stdio.h>

int list_op_flag(void)
{
    char *buffer = copy_content_file("src/binary_flag/.list_op");

    if (buffer == NULL)
        return 84;
    printf("%s", buffer);
    return 0;
}

int list_flag(void)
{
    char *buffer = copy_content_file("src/binary_flag/.list_command");

    if (buffer == NULL)
        return 84;
    printf("%s", buffer);
    return 0;
}
