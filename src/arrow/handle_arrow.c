/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** handle_arrow
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

void arrow_check(char c, stock_t *sk)
{
    if (c == '\033') {
        read(STDIN_FILENO, &c, 1);
        if (c == '[') {
            read(STDIN_FILENO, &c, 1);
            switch (c) {
                case 'A': arrow_up(sk); break;
                case 'B': arrow_down(sk); break;
                case 'C': ; break;
                case 'D': ; break;
                default: printf("autre touche spéciale\n"); break;
            }
        }
    }
}
