/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

int setenv_error_handling2(char **array)
{
    for (int i = 0; array[1][i] != '\0'; i++) {
        if ((array[1][i] < '0') || (array[1][i] > '9' && array[1][i] < 'A') ||
        (array[1][i] > 'Z' && array[1][i] < 'a') || (array[1][i] > 'z')) {
            my_putstr_error("setenv: Variable name must contain ");
            my_putstr_error("alphanumeric characters.\n");
            return (1);
        }
    }
    return (0);

}

int setenv_error_handling(char **array, int i)
{
    int check = 1;

    if (i > 3) {
        my_putstr_error("setenv: Too many arguments.\n");
        return (1);
    }
    if (i > 1) {
        if ((array[1][0] < 'A') || (array[1][0] > 'Z' && array[1][0] < 'a') ||
            (array[1][0] > 'z')) {
            my_putstr_error("setenv: Variable name must begin ");
            my_putstr_error("with a letter.\n");
            return (1);
        }
        check = setenv_error_handling2(array);
        if (check != 0)
            return check;
    }
    return (0);

}
