/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** free_main_exec
*/

#include <stdlib.h>
#include "my.h"

void free_main_exec(stock_t *sk)
{
    free_array(sk->array_pipe);
    free_array(sk->array_duck);
    free_array(sk->array_reverse_duck);
    free_array(sk->array_space);
}
