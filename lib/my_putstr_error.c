/*
** EPITECH PROJECT, 2022
** my_putstr_error
** File description:
** print error
*/

#include <unistd.h>
#include "my.h"

void my_putstr_error(char *str)
{
    write(2, str, my_strlen(str));
}
