/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"
#include "my_list.h"

int main(int ac, const char **av)
{
    if (ac == 1)
        return my_nm("a.out");
    else
        return my_nm_on_files(av + 1, ac - 1);
}
