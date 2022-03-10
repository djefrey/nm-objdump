/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-objdumpobjdump-jeffrey.winkler
** File description:
** main
*/

#include <stdio.h>
#include <ar.h>
#include "objdump.h"

int main(int ac, const char **av)
{
    if (ac == 1)
        return my_objdump("a.out");
    else
        return my_objdump_on_files(av + 1, ac - 1);
}
