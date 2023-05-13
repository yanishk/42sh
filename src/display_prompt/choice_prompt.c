/*
** EPITECH PROJECT, 2023
** B-PSU-200-PAR-2-1-42sh-yanis.harkouk
** File description:
** choice_prompt
*/

#include "my.h"

int choice_prompt(stock_t *sk, char *current_path, char **cpy_env)
{
    int size = sk->check_st.size_term;
    if (size < 88)
        print_prompt(sk, current_path, cpy_env);
    if (size > 88)
        print_prompt2(sk, current_path, cpy_env);
    return 0;
}
