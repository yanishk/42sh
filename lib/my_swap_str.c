/*
** EPITECH PROJECT, 2022
** my_swap.c
** File description:
** pool
*/

#include <unistd.h>
#include <stdio.h>
#include "my.h"

void my_swap_str(char **a, char **b)
{
    char *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
