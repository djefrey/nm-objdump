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

int main(int ac, char **av)
{
    Elf64_Ehdr *hdr = open_elf_file(av[1]);

    print_symbols_from_elf(hdr);
}