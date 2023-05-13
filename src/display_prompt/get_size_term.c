/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** get_term_size
*/

#include <sys/ioctl.h>

int get_size_term(void)
{
    struct winsize size;
    int cols = 0;

    ioctl(0, TIOCGWINSZ, &size);
    cols = size.ws_col;
    return cols;
}
